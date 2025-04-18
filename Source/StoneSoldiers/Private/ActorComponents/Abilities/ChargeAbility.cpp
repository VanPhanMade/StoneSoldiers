/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/

#include "ActorComponents/Abilities/ChargeAbility.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Actors/TileMap.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

void UChargeAbility::Init(ABaseUnit* Unit)
{
	Super::Init(Unit);

	Unit->OnBeginMoveDelegate.AddDynamic(this, &UChargeAbility::FindAdjacentUnits);
	Unit->OnCombatTargetDelegate.AddDynamic(this, &UChargeAbility::CheckWasTargetAdjacent);
	Unit->OnTurnFinishedDelegate.AddDynamic(this, &UChargeAbility::ResetStrength);

	UWorld* World = GetWorld();
	GameState = World->GetGameState<AStoneSoldiersGameState>();
}

void UChargeAbility::FindAdjacentUnits()
{
	AdjacentUnits.Empty();
	AdjacentUnits = GameState->TileMap->GetNeighboringUnits(OwningUnit->TileCoords);
	//StoneSoldiersHelperFunctions::LogEngineMessage(FString("Num Adjacent Units: ") + FString::FromInt(AdjacentUnits.Num()));
}

void UChargeAbility::CheckWasTargetAdjacent(ABaseUnit* Target)
{
	TArray<ABaseUnit*> SurroundingUnits = GameState->TileMap->GetNeighboringUnits(OwningUnit->TileCoords);

	if (!AdjacentUnits.Contains(Target) && SurroundingUnits.Contains(Target))
	{
		OwningUnit->SetStrength(OwningUnit->GetStrength() + 2);
		return;
	}

	//StoneSoldiersHelperFunctions::LogEngineMessage(FString("Charge Failed"));
}

void UChargeAbility::ResetStrength(ABaseUnit* Unit)
{
	// Resets the Strength of the Unit
	OwningUnit->ResetStrength();
}
