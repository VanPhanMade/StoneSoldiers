// ©Van Phan


#include "Actors/UnitTile.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "ActorComponents/BaseActionComponent.h"
#include "Actors/CursorIndicator.h"
#include "Actors/TileMap.h"
#include "Actors/CursorIndicator.h"
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
	//TileData = TileVisualsDataTable->FindRow<FTileData>(SelectedTileRowName, TEXT("UpdateTileVisuals"));
	//UpdateTilesFromSelection();
}

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

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	if (PlayerState->GoToStateFromCurrent("Moving Unit"))
	{
		// Update UI
		GameState->GetCursorIndicator()->DisplayCharacterInfo(false, false);
		GameState->GetCursorIndicator()->DisplayCursorMesh(false);
	}

	
}



/// <summary>
/// Left Click Delegate Function that Moves Unit To This Tile
/// </summary>
void AUnitTile::ManageMoveToTile()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	PlayerState->GoToStateFromCurrent("Choosing Unit Action");
	
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

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
	PlayerState->GoToStateFromCurrent("My Turn");

	GameState->ActiveUnit->EndTurn();
}

/// <summary>
/// Executes the OnLeftClick Delegate.
/// </summary>
void AUnitTile::OnLeftClick()
{
	if (OnLeftClickDelegate.IsBound()) OnLeftClickDelegate.Execute();
	else UE_LOG(LogTemp, Warning, TEXT("On Left click has nothing bound. | AUnitTile | OnLeftClick"));
}

/// <summary>
/// Right Click Function
/// </summary>
void AUnitTile::OnRightClick()
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
				APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
				AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();

				// Logic specific to the 3D cursor and unit info UI popup
				if (PlayerState->GetCurrenState()->StateName == "My Turn" || PlayerState->GetCurrenState()->StateName == "Not My Turn"  )
				{
					// Swap cursor to show only one
					GameState->GetCursorIndicator()->SetActorLocation(GetActorLocation());
					GameState->GetCursorIndicator()->DisplayCharacterInfo(OccupyingUnit != nullptr, false);
					GameState->GetCursorIndicator()->DisplayCursorMesh(true);
				}
				else
				{
					GameState->GetCursorIndicator()->DisplayCharacterInfo(false, false);
					GameState->GetCursorIndicator()->DisplayCursorMesh(false);
				}

				// Logic specific to the spline used to indicate targetting
				if (PlayerState->GetCurrenState()->StateName == "Moving Unit" || PlayerState->GetCurrenState()->StateName == "Targeting Unit Action")
				{
					GameState->GetMovementSpline()->SetVisibilityForSpline(true);
					if (GameState->ActiveUnit)
					{
						GameState->GetMovementSpline()->UpdateSplineMeshes(GameState->ActiveUnit->GetActorLocation(), GetActorLocation());
					}

					if (PlayerState->GetCurrenState()->StateName == "Targeting Unit Action")
					{
						GameState->GetCursorIndicator()->DisplayCharacterInfo(OccupyingUnit != nullptr, true);
						// Swap cursor to show both unit vs one
					}
				}
				else
				{
					GameState->GetMovementSpline()->SetVisibilityForSpline(false);
				}
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

/// <summary>
/// Initializes the Class
/// </summary>
void AUnitTile::Init()
{
	OnLeftClickDelegate.BindUObject(this, &AUnitTile::ManageBaseLeftClick);
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


