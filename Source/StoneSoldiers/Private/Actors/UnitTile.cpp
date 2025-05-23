/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Actors/UnitTile.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "ActorComponents/BaseActionComponent.h"
#include "Actors/CursorIndicator.h"
#include "Actors/TileMap.h"
#include "PlayerStates/StoneSoldierPlayerState.h"
#include "Actors/MovementVisualSpline.h"

// Constructor
AUnitTile::AUnitTile()
{
	PrimaryActorTick.bCanEverTick = true;

	// Establishes Component Tree
	if (!RootComponent) RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Mesh"));
	MainMesh->SetupAttachment(RootComponent);
	HoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hover Mesh"));
	HoverMesh->SetupAttachment(RootComponent);
	SelectionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selection Mesh"));
	SelectionMesh->SetupAttachment(RootComponent);
}

void AUnitTile::BeginPlay()
{
	Super::BeginPlay();
}

void AUnitTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// The default left click delegate function
/// @param InstigatorActor The actor that initiated the click action.
void AUnitTile::ManageBaseLeftClick(AActor* InstigatorActor)
{
	// If GameState Active Unit exists, return
	if (GameState->ActiveUnit != nullptr)
	{
		StoneSoldiersHelperFunctions::LogEngineMessage(FString("Already an active unit selected! | AUnitTile"));
		return;
	}

	// Does This Tile Possess a Unit
	if (OccupyingUnit == nullptr)
	{
		StoneSoldiersHelperFunctions::LogEngineMessage(FString("Empty Tile | AUnitTile"));
		return;
	}

	// If the Unit is not controlled by the active player, or the Unit Is Finished, Return Stats
	if (OccupyingUnit->State == EUnitState::Finished)
	{
		// DISPLAY STATS
		StoneSoldiersHelperFunctions::LogEngineMessage(FString("Unit Finished"));
		return;
	}

	if (OccupyingUnit->OwningPlayer != GameState->ActivePlayer)
	{
		StoneSoldiersHelperFunctions::LogEngineMessage(FString("Not Owned Player"));
		return;
	}

	// If the Unit is Idle, Calculate Movement and Set Next Delegate
	GameState->ActiveUnit = OccupyingUnit;
	TArray<AUnitTile*> MoveableTiles = GameState->TileMap->CalculateMove(Coordinates, OccupyingUnit->GetUnitData().UnitCoreData.Movement, OccupyingUnit->MovementFilter);
	for (AUnitTile* Tile : MoveableTiles)
	{
		GameState->TileMap->MakeTileMoveable(Tile);
	}

	APlayerController* PlayerController = Cast<APlayerController>(InstigatorActor);
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	PlayerState->GoToStateFromCurrent("Moving Unit");
}

/// Left Click Delegate Function that Moves Unit To This Tile
/// @param InstigatorActor The actor that initiated the move.
void AUnitTile::ManageMoveToTile(AActor* InstigatorActor)
{
	APlayerController* PlayerController = Cast<APlayerController>(InstigatorActor);
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	PlayerState->GoToStateFromCurrent("Choosing Unit Action");
	GameState->MoveUnit(this);
}

/// Left Click Delegate Function that manages a combat action targeting this tile's unit
/// @param InstigatorActor The actor that initiated the combat action.
void AUnitTile::ManageCombat(AActor* InstigatorActor)
{
	GameState->ActiveUnit->OnCombatTargetDelegate.Broadcast(OccupyingUnit);
	GameState->ActiveUnit->Actions[0]->UseAction(OccupyingUnit);

	APlayerController* PlayerController = Cast<APlayerController>(InstigatorActor);
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	PlayerState->GoToStateFromCurrent("My Turn");

	GameState->ActiveUnit->EndTurn();
}

/**
 * Executes the OnLeftClick delegate.
 * @param InstigatorActor The actor that initiated the click action.
 */
void AUnitTile::OnLeftClick(AActor* InstigatorActor)
{
	if (OnLeftClickDelegate.IsBound()) OnLeftClickDelegate.Broadcast(InstigatorActor);
	else UE_LOG(LogTemp, Warning, TEXT("On Left click has nothing bound. | AUnitTile | OnLeftClick"));
}

/// Right Click Function
/// @param InstigatorActor The actor that initiated the right-click action.
void AUnitTile::OnRightClick(AActor* InstigatorActor)
{
	if (TileData)
	{
		if (TileData->TileVisuals.OnSelectionMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
		}
	}
}

/// Highlights the tile. Used to indicate selectable tiles for moving/actions.
void AUnitTile::HighlightTile()
{
	SelectionMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
}

/// Unhighlights the tile.
void AUnitTile::UnhighlightTile()
{
	SelectionMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);
}

/// When user's mouse enters tile
/// @param InstigatorActor The actor that initiated the hover.
void AUnitTile::OnHoverBegin(AActor* InstigatorActor)
{
	if (TileData)
	{
		if (TileData->TileVisuals.OnHoverMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnHoverMaterial);
			if (GameState)
			{
				APlayerController* PlayerController = Cast<APlayerController>(InstigatorActor);
				AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();

				// Logic specific to the 3D cursor and unit info UI popup
				if (PlayerState->GetCurrenState()->StateName == "My Turn" || PlayerState->GetCurrenState()->StateName == "Not My Turn"  )
				{
					// Swap cursor to show only one
					GameState->GetCursorIndicator()->SetActorLocation(GetActorLocation());
					GameState->GetCursorIndicator()->DisplayCharacterInfo(OccupyingUnit != nullptr, false, nullptr, OccupyingUnit);
				}

				// Logic specific to the spline used to indicate targeting
				if (PlayerState->GetCurrenState()->StateName == "Moving Unit" || PlayerState->GetCurrenState()->StateName == "Targeting Unit Action")
				{
					if (GameState->ActiveUnit.Get())
					{
						GameState->GetMovementSpline()->UpdateSplineMeshes(GameState->ActiveUnit->GetActorLocation(), GetActorLocation());
					}

					if (PlayerState->GetCurrenState()->StateName == "Targeting Unit Action")
					{
						GameState->GetCursorIndicator()->DisplayCharacterInfo(OccupyingUnit != nullptr, true, GameState->ActiveUnit.Get(), OccupyingUnit);
					}
				}
			}
			
		}
	}
}

/// When user's mouse leaves tile
/// @param InstigatorActor The actor that initiated the hover end.
void AUnitTile::OnHoverEnd(AActor* InstigatorActor)
{
	if (TileData)
	{
		if (TileData->TileVisuals.OverlayBaseMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);
		}
	}
}

/// Initializes the Class
void AUnitTile::Init()
{
	if (!OnLeftClickDelegate.IsAlreadyBound(this, &AUnitTile::ManageBaseLeftClick))
	{
		OnLeftClickDelegate.AddDynamic(this, &AUnitTile::ManageBaseLeftClick);
	}
	if (UWorld* World = GetWorld()) GameState = World->GetGameState<AStoneSoldiersGameState>();
}

/// Shows the tile as moveable.
void AUnitTile::ShowMoveable()
{
	if (TileData)
	{
		if (TileData->TileVisuals.OnSelectionMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
		}
	}
}

/// Spawns a unit on the tile
/// @returns Returns the unit that was spawned.
AActor* AUnitTile::SpawnUnit()
{
	FTransform Transform = HoverMesh->GetComponentTransform();
	OccupyingUnit = GetWorld()->SpawnActor<ABaseUnit>(GameState->TempUnit, Transform);
	return OccupyingUnit;
}

/// Updates the tiles information from the TileVisualsData
void AUnitTile::UpdateTilesFromSelection()
{
	if (TileVisualsDataTable)
	{
		if (TileData)
		{
			if (TileData->TileVisuals.BaseStaticMesh && TileData->TileVisuals.OverlayMesh && TileData->TileVisuals.OverlayBaseMaterial)
			{
				MainMesh->SetStaticMesh(TileData->TileVisuals.BaseStaticMesh);
				MainMesh->SetMaterial(0, TileData->TileVisuals.BaseStaticMeshMaterial);

				HoverMesh->SetStaticMesh(TileData->TileVisuals.OverlayMesh);
				HoverMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);

				SelectionMesh->SetStaticMesh(TileData->TileVisuals.OverlayMesh);
				SelectionMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);

				SetActorScale3D(TileData->TileVisuals.TileScale);
			}
			else
			{
				StoneSoldiersHelperFunctions::LogEngineMessage("Issue loading in tile data!");
			}
		}
		else
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("Invalid row index!");
		}
	}
}

/// Updates the tile type based on the terrain type.
void AUnitTile::UpdateTileType()
{
	switch (TerrainType)
	{
		case ETerrainType::Blank:
			break;
		case ETerrainType::Grass:
			MovementCost = 1;
			break;
		case ETerrainType::Forest:
			MovementCost = 2;
			// Provides Cover
			break;
		case ETerrainType::Mud:
			MovementCost = 2;
			break;
		case ETerrainType::ShallowWater:
			MovementCost = 3;
			break;
		case ETerrainType::DeepWater:
			MovementCost = 100;
			break;
		case ETerrainType::Mountain:
			// Blocks Line of Sight
			MovementCost = 100;
			break;
		case ETerrainType::Lava:
			// Harms the Unit
			MovementCost = 3;
			break;
	}
}


