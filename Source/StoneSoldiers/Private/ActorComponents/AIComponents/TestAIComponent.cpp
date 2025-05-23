/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "ActorComponents/AIComponents/TestAIComponent.h"
#include "Actors/UnitTile.h"
#include "Actors/TileMap.h"
#include "Actors/BaseUnit.h"
#include "ActorComponents/BaseActionComponent.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"


void UTestAIComponent::RunUnit()
{
	//Super::RunUnit();

	switch (UnitStance)
	{
		case EUnitAIStance::Static:
			StationaryBehavior();
			break;

		case EUnitAIStance::Standard:
			StandardBehavior();
			break;

		default:
			break;
	}

}

void UTestAIComponent::GetBehavior(EUnitAIStance Stance)
{
	Super::GetBehavior(Stance);
}

// With this behavior, Unit Doesn't Move But Will Attack if an enemy is in range
void UTestAIComponent::StationaryBehavior()
{
	// Target Move Coord Remains the same

	// Sets the Action to the Attack Action
	ManageAttackAction();
}


void UTestAIComponent::StandardBehavior()
{
	// Moves Towards the Closest Enemy Unit
	MoveAtNearest();

	// Attacks the best nearby target
	ManageAttackAction();
}

void UTestAIComponent::MoveAtNearest()
{

	// Get Enemy Units
	TArray<ABaseUnit*> EnemyUnits;
	for (const auto& TeamPair : GameState->TeamUnits)
	{
		ETeamID TeamID = TeamPair.Key;

		// Skip own team
		if (TeamID == ETeamID::Team2) continue;

		for (const TWeakObjectPtr<ABaseUnit>& UnitPtr : TeamPair.Value)
		{
			if (UnitPtr.IsValid())
			{
				EnemyUnits.Add(UnitPtr.Get());
			}
		}
	}

	// Finds Closest Enemy
	ABaseUnit* ClosestUnit = nullptr;
	int ClosestUnitDistance = 1000;
	for (int i = 0; i < EnemyUnits.Num(); i++)
	{
		int dist = GameState->TileMap->GetDistanceBetweenTiles(OwningUnit->TileCoords, EnemyUnits[i]->TileCoords);
		if (ClosestUnitDistance > dist)
		{
			ClosestUnit = EnemyUnits[i];
			ClosestUnitDistance = dist;
		}
	}

	// Moves Towards ClosestUnit
	if (ClosestUnit != nullptr)
	{
		//StoneSoldiersHelperFunctions::LogEngineMessage("Closest Unit: " + ClosestUnit->TileCoords.ToString());

		bool result = false;
		int StepsBack = 0;
		while (result == false)
		{
			TArray<AUnitTile*> Path = GameState->TileMap->GetPathToTarget(OwningUnit->TileCoords, ClosestUnit->TileCoords, OwningUnit->MovementFilter);
			result = GameState->MoveUnit(GameState->TileMap->FollowPath(Path, OwningUnit->GetUnitData().UnitCoreData.Movement - StepsBack, OwningUnit->MovementFilter));
			StepsBack++;
		}
		
	}
	
}

void UTestAIComponent::ManageAttackAction()
{
	// Gets the appropriate tiles that can be targeted.
	TArray<AUnitTile*> ValidTiles = GameState->TileMap->GetTargetableTiles(OwningUnit->TileCoords, OwningUnit->CurrentWeapon.Range);

	if (ValidTiles.Num() == 0)
	{
		return;
	}

	// Give Each Unit a Target Priority, Starting by Maximizing Damage
	ABaseUnit* BestUnit = nullptr;
	int BestUnitScore = -1;
	for (int i = 0; i < ValidTiles.Num(); i++)
	{
		ABaseUnit* Unit = ValidTiles[i]->GetOccupyingUnit();
		int Score = OwningUnit->GetCurrentWeaponDamage() - Unit->GetCurrentDefenses()[OwningUnit->CurrentWeapon.DamageType];

		if (Score > BestUnitScore)
		{
			BestUnit = Unit;
			BestUnitScore = Score;
		}
	}

	// Attacks the Best Target
	OwningUnit->Actions[0]->UseAction(BestUnit);
}
