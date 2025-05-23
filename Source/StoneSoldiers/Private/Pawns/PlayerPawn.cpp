/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Pawns/PlayerPawn.h"

#include "Actors/GolemUnit.h"
#include "Actors/StoneCasterUnit.h"
#include "Actors/UnitTile.h"
#include "GameModes/SS_Gamemode_Singleplayer.h"
#include "PlayerControllers/StoneSoldiersPlayerController.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

/// Resets units to be in the "ready" state
void APlayerPawn::StartPlayerTurn()
{
	UWorld* World = GetWorld();
	AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();
	UnitsToActivate = GameState->PlayerUnits[ID];

	for (TWeakObjectPtr<ABaseUnit> UnitToReset : UnitsToActivate)
	{
		if (UnitToReset.IsValid())
		{
			UnitToReset->State = EUnitState::Ready;
		}
		else
		{
			StoneSoldiersHelperFunctions::LogEngineMessage(TEXT("Null unit in UnitsToActivate | SinglePlayerPawn | StartPlayerTurn"));
		}
	}
}

/// Handles instantiation of units from desired units to spawn array
/// Also handles connect units to proper array/reference relationships
void APlayerPawn::SpawnUnits()
{
	UWorld* World = GetWorld();
	ABaseUnit* Unit = nullptr;
	AStoneCasterUnit* PreviousStoneCaster = nullptr;

	for (int i = 0; i < SelectedUnitData.Num(); i++)
	{
		FTransform Transform = FTransform();
		FVector Location = GetActorLocation() + FVector(0.0, i * 150, 0.0);
		Transform.SetLocation(Location);

		Unit = Cast<ASS_Gamemode_Singleplayer>(World->GetAuthGameMode())->CreateUnit(SelectedUnitData[i]);
		if (Unit == nullptr)
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("Failed to retrieve unit! | APlayerPawn | SpawnUnits");
			return;
		}
		Unit->Init(SelectedUnitData[i], ID);
		
		if (Unit->GetUnitData().Type == StoneCaster)
		{
			PreviousStoneCaster = Cast<AStoneCasterUnit>(Unit);
		}
		
		if (Unit->GetUnitData().Type == Golem)
		{
			PreviousStoneCaster->AddControlledGolem(Cast<AGolemUnit>(Unit));
			Cast<AGolemUnit>(Unit)->SetControllingCaster(PreviousStoneCaster);
		}

		if (Unit != nullptr)
		{
			ControlledUnits.Add(Unit);
		}
	}

	if (AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>())
	{
		GameState->PlayerUnits.Add(ID, ControlledUnits);
		GameState->TeamUnits.Add(TeamID, ControlledUnits);
		
	}
	
}

/// Places units into tile map based of Vector3 hex coords 
void APlayerPawn::PlaceUnits()
{
	if (AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>())
	for (int i = 0; i < ControlledUnits.Num(); i++)
	{
		GameState->PlaceUnit(ControlledUnits[i].Get(), StartingPositions[i]);
	}
}

///	Destroy a unit we have ownership over
/// Handles cleaning up loose references for the unit and cleaning up containers
/// @param Unit The unit being destroyed
void APlayerPawn::DestroyUnit(class ABaseUnit* Unit)
{
	if (AStoneSoldiersGameState* GS = GetWorld()->GetGameState<AStoneSoldiersGameState>())
	{
		if (GS->TeamUnits.Contains(TeamID))
		{
			GS->TeamUnits[TeamID].Remove(Unit);
			if (GS->TeamUnits[TeamID].Num() == 0) GS->TeamUnits.Remove(TeamID);
		}
		
		if (GS->PlayerUnits.Contains(ID))
		{
			GS->PlayerUnits[ID].Remove(Unit);
			if (GS->PlayerUnits[ID].Num() == 0) GS->PlayerUnits.Remove(ID);
		}

		if (GS->Tiles.Contains(Unit->TileCoords))
		{
			GS->Tiles[Unit->TileCoords]->SetOccupyingUnit(nullptr);
		}

		if (ControlledUnits.Contains(Unit))
		{
			ControlledUnits.Remove(Unit);
		}

		// Removing nullptr / garbage collected units
		ControlledUnits.RemoveAll([](const TWeakObjectPtr<ABaseUnit>& Unit)
		{
			return !Unit.IsValid();
		});

		UnitsToActivate.RemoveAll([](const TWeakObjectPtr<ABaseUnit>& Unit)
		{
			return !Unit.IsValid();
		});

		if (GS->TeamUnits.Contains(TeamID))
		{
			GS->TeamUnits[TeamID].RemoveAll([](const TWeakObjectPtr<ABaseUnit>& Unit)
			{
				return !Unit.IsValid();
			});
			if (GS->TeamUnits[TeamID].Num() == 0)
			{
				GS->TeamUnits.Remove(TeamID);
			}
		}

		if (GS->PlayerUnits.Contains(ID))
		{
			GS->PlayerUnits[ID].RemoveAll([](const TWeakObjectPtr<ABaseUnit>& Unit)
			{
				return !Unit.IsValid();
			});
			if (GS->PlayerUnits[ID].Num() == 0)
			{
				GS->PlayerUnits.Remove(ID);
			}
		}
	}
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld()) World->GetGameState<AStoneSoldiersGameState>()->RegisterPlayer(ID, this);
	
	SpawnUnits();
	PlaceUnits();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

