// ©Van Phan


#include "Actors/UnitTile.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "ActorComponents/BaseActionComponent.h"
#include "Actors/CursorIndicator.h"
#include "Actors/TileMap.h"
#include "Actors/CursorIndicator.h"

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

// BeginPlay
void AUnitTile::BeginPlay()
{
	Super::BeginPlay();
	//TileData = TileVisualsDataTable->FindRow<FTileData>(SelectedTileRowName, TEXT("UpdateTileVisuals"));
	//UpdateTilesFromSelection();
}

// Tick
void AUnitTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// The default left click delegate function
/// </summary>
void AUnitTile::ManageBaseLeftClick()
{
	// If GameState Active Unit exists, return
	if (GameState->ActiveUnit != nullptr)
	{
		StoneSoldiersHelperFunctions::LogEngineMessage(FString("Not Valid Tile For Moving/Action"));
		return;
	}

	// Does This Tile Possess a Unit
	if (OccupyingUnit == nullptr)
	{
		StoneSoldiersHelperFunctions::LogEngineMessage(FString("No Unit On Tile"));
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

	
}



/// <summary>
/// Left Click Delegate Function that Moves Unit To This Tile
/// </summary>
void AUnitTile::ManageMoveToTile()
{
	StoneSoldiersHelperFunctions::LogEngineMessage(FString("Moving"));
	GameState->MoveUnit(this);
}

/// <summary>
/// Left Click Delegate Function that manages a combat action targeting this tile's unit
/// </summary>
void AUnitTile::ManageCombat()
{
	StoneSoldiersHelperFunctions::LogEngineMessage(FString("Successful Attack"));

	GameState->ActiveUnit->OnCombatTargetDelegate.Broadcast(OccupyingUnit);

	GameState->ActiveUnit->Actions[0]->UseAction(OccupyingUnit);

	GameState->ActiveUnit->EndTurn();
}

/// <summary>
/// Executes the OnLeftClick Delegate.
/// </summary>
void AUnitTile::OnLeftClick()
{
	OnLeftClickDelegate.Execute();
}

/// <summary>
/// Right Click Function
/// </summary>
void AUnitTile::OnRightClick()
{
	StoneSoldiersHelperFunctions::LogEngineMessage("Right clicked");
	if (TileData)
	{
		if (TileData->TileVisuals.OnSelectionMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
		}
	}
}

/// <summary>
/// Highlights the tile. Used to indicate selectable tiles for moving/actions
/// </summary>
void AUnitTile::HighlightTile()
{
	SelectionMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
}

/// <summary>
/// Unhighlights the tile
/// </summary>
void AUnitTile::UnhighlightTile()
{
	SelectionMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);
}

/// <summary>
/// When user's mouse enters tile
/// </summary>
void AUnitTile::OnHoverBegin()
{
	if (TileData)
	{
		if (TileData->TileVisuals.OnHoverMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnHoverMaterial);
			if (GameState)
			{
				GameState->GetCursorIndicator()->SetActorLocation(GetActorLocation());
				GameState->GetCursorIndicator()->DisplayCharacterInfo(OccupyingUnit != nullptr);
			}
			
		}
	}

}

/// <summary>
/// When user's mouse leaves tile
/// </summary>
void AUnitTile::OnHoverEnd()
{
	if (TileData)
	{
		if (TileData->TileVisuals.OverlayBaseMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);
		}
	}
}

//FVector Coords, UDataTable* Data, FName RowName

/// <summary>
/// Initializes the Class
/// </summary>
void AUnitTile::Init()
{
	OnLeftClickDelegate.BindUObject(this, &AUnitTile::ManageBaseLeftClick);
	/*Coordinates = Coords;
	SelectedTileRowName = RowName;
	TileVisualsDataTable = Data;

	TileData = TileVisualsDataTable->FindRow<FTileData>(SelectedTileRowName, TEXT("UpdateTileVisuals"));
	UpdateTilesFromSelection();

	*/
	if (UWorld* World = GetWorld()) GameState = World->GetGameState<AStoneSoldiersGameState>();
	
}

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

/// <summary>
/// Spawns a unit on the tile
/// </summary>
/// <returns>Returns the unit that was spawned</returns>
AActor* AUnitTile::SpawnUnit()
{
	FTransform Transform = HoverMesh->GetComponentTransform();
	OccupyingUnit = GetWorld()->SpawnActor<ABaseUnit>(GameState->TempUnit, Transform);
	return OccupyingUnit;
}

/// <summary>
/// Updates the tiles information from the TileVisualsData
/// </summary>
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


