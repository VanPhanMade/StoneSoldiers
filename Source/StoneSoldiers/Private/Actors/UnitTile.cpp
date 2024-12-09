// ©Van Phan


#include "Actors/UnitTile.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Actors/TileMap.h"

AUnitTile::AUnitTile()
{
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent) RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Mesh"));
	MainMesh->SetupAttachment(RootComponent);
	HoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hover Mesh"));
	HoverMesh->SetupAttachment(RootComponent);
}

void AUnitTile::OnLeftClick()
{
	
	if(TileData)
	{
		UWorld* World = GetWorld();
		if (AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>())
		{
			if (GameState->TileMap->MoveableTiles.Contains(this) && GameState->SelectedTile != nullptr && GameState->SelectedTile->GetOccupyingUnit()->CanActivate)
			{
				//StoneSoldiersHelperFunctions::LogEngineMessage("Moving");
				GameState->MoveUnit(this);
			}
			else if(TileData->TileVisuals.OnSelectionMaterial && OccupyingUnit != nullptr)
			{
				//StoneSoldiersHelperFunctions::LogEngineMessage("Selecting tile with unit");
				HoverMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
				
				GameState->TileMap->CalculateMove(Coordinates, OccupyingUnit->GetUnitData().UnitCoreData.Movement, OccupyingUnit->MovementFilter);
			}
		}
		else
		{
			StoneSoldiersHelperFunctions::LogEngineMessage("Can't retrieve game state");
		}

		
	}
} 

void AUnitTile::OnRightClick()
{
	StoneSoldiersHelperFunctions::LogEngineMessage("Right clicked");
	if(TileData)
	{
		if(TileData->TileVisuals.OnSelectionMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
		}
	}
}

void AUnitTile::OnHoverBegin()
{
	if(TileData)
	{
		if(TileData->TileVisuals.OnHoverMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnHoverMaterial);
		}
	}

}

void AUnitTile::OnHoverEnd()
{
	if(TileData)
	{
		if(TileData->TileVisuals.OverlayBaseMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);
		}
	}
}

void AUnitTile::Init(FVector Coords, UDataTable *Data, FName RowName)
{
	Coordinates = Coords;
	SelectedTileRowName = RowName;
	TileVisualsDataTable = Data;

	TileData = TileVisualsDataTable->FindRow<FTileData>(SelectedTileRowName, TEXT("UpdateTileVisuals"));
	UpdateTilesFromSelection();
}

void AUnitTile::ShowMoveable()
{
	if(TileData)
	{
		if(TileData->TileVisuals.OnSelectionMaterial)
		{
			HoverMesh->SetMaterial(0, TileData->TileVisuals.OnSelectionMaterial);
		}
	}
}

AActor* AUnitTile::SpawnUnit()
{
	UWorld* World = GetWorld();
	AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();
	FTransform Transform = HoverMesh->GetComponentTransform();
	OccupyingUnit = World->SpawnActor<ABaseUnit>(GameState->TempUnit, Transform);
	return OccupyingUnit;
}

void AUnitTile::BeginPlay()
{
	Super::BeginPlay();
	TileData = TileVisualsDataTable->FindRow<FTileData>(SelectedTileRowName, TEXT("UpdateTileVisuals"));
	UpdateTilesFromSelection();
}

void AUnitTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitTile::UpdateTilesFromSelection()
{
	if(TileVisualsDataTable)
	{
		if(TileData)
		{
			if(TileData->TileVisuals.BaseStaticMesh && TileData->TileVisuals.OverlayMesh && TileData->TileVisuals.OverlayBaseMaterial)
			{
				MainMesh->SetStaticMesh(TileData->TileVisuals.BaseStaticMesh);
				MainMesh->SetMaterial(0, TileData->TileVisuals.BaseStaticMeshMaterial);

				HoverMesh->SetStaticMesh(TileData->TileVisuals.OverlayMesh);
				HoverMesh->SetMaterial(0, TileData->TileVisuals.OverlayBaseMaterial);

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
