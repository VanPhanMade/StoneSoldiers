// ©Van Phan 


#include "Actors/TileMap.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Actors/UnitTile.h"
#include "GameModes/SS_Gamemode_Singleplayer.h"
#include "GameModes/StoneSoldiersGameMode.h"
#include "GameStates/StoneSoldiersGameState.h"

const float SQRTof3 = FMath::Sqrt(3.0f);

ATileMap::ATileMap()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATileMap::BeginPlay()
{
	Super::BeginPlay();
	if(RowBounds == 0 || ColumnBounds == 0)
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Rows and columns invalid for Tile Map!");
	}
	else
	{
		BuildMap(RowBounds, ColumnBounds);
	}
	
}

void ATileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileMap::BuildMap(int Rows, int Columns)
{
	if (!IsValid(TileClass))
		return;

	// Ensure we're on the server version of actor
	if(Cast<ASS_Gamemode_Singleplayer>(GetWorld()->GetAuthGameMode()) || Cast<AStoneSoldiersGameMode>(GetWorld()->GetAuthGameMode()))
	{
		UWorld* World = GetWorld();
		if(AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>())
		switch(TileType)
		{
			case ETileType::Square:
				
				break;

			case ETileType::Triangle:

				break;

			case ETileType::Hexagon:
				GameState->AddTileMap(this);

				for (int i = 0; i < Rows; i++)
				{
					for (int k = 0; k < Columns; k++)
					{
						FVector Location = FirstHexPosition;
						Location.X = Location.X + (SQRTof3 * k * 55) + (0.5 * SQRTof3 * (i % 2) * 55);
						Location.Y = Location.Y + (1.5 * i * 55);

						FQuat Quaternion = FQuat(FVector(0.0f, 0.0f, 1.0f), FMath::DegreesToRadians(30.0f));

						FTransform SpawnTransform = GetActorTransform();
						SpawnTransform.SetLocation(SpawnTransform.TransformPosition(Location));
						SpawnTransform.SetRotation(Quaternion);

						float q = k - (i - (i&1)) / 2;
						FVector CubeCoord = FVector(q, i, -q-i);
						if (FMath::IsNearlyEqual(CubeCoord.Z, 0.0f)) CubeCoord.Z = 0.0f;

						GameState->AddTiles(World->SpawnActor<AUnitTile>(TileClass, SpawnTransform), CubeCoord);
					}
				}
				break;

			default:
				StoneSoldiersHelperFunctions::LogEngineMessage("No valid Tile Type selected for map generation!");
				break;
		}
	}
	
	
}

AUnitTile* ATileMap::GetNeighbor(FVector StartHex, FVector Direction)
{
	AUnitTile* Tile = NULL;
	UWorld* World = GetWorld();
	if(AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>())
	{
		FVector Coords = StartHex + Direction;
		if (GameState->Tiles.Contains(Coords))
		{
			Tile = GameState->Tiles[StartHex + Direction];
		}
		
	}

	return Tile;
}

void ATileMap::ClearMoveableTiles()
{
	for (int i = 0; i < MoveableTiles.Num(); i++)
	{
		MoveableTiles[i]->OnHoverEnd();
	}
	MoveableTiles.Empty();
}

TArray<ABaseUnit*> ATileMap::GetNeighboringUnits(FVector StartingHex)
{
	TArray<ABaseUnit*> AdjacentUnits = TArray<ABaseUnit*>();

	for (int i = 0; i < Directions.Num(); i++)
	{
		AUnitTile* NeighborHex = GetNeighbor(StartingHex, Directions[i]);
		if (NeighborHex != nullptr && NeighborHex->GetOccupyingUnit() != nullptr) AdjacentUnits.Add(NeighborHex->GetOccupyingUnit());
	}

	return AdjacentUnits;
}

bool ATileMap::CalculateMove(FVector StartingHex, int range, TMap<ETerrainType, uint8> Filter)
{
	ClearMoveableTiles();

	UWorld* World = GetWorld();
	if(AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>())
	{
		AUnitTile* StartingTile = GameState->Tiles[StartingHex];
		GameState->SelectedTile = StartingTile;

		TMap<AUnitTile*, int> VisitedTiles;
		//TArray<AUnitTile*> VisitedTiles;
		VisitedTiles.Add(StartingTile, range);
		StartingTile->ShowMoveable();
		MoveableTiles.Add(StartingTile);
		TArray<TArray<AUnitTile*>> Fringes;
		Fringes.Add(TArray<AUnitTile*> {StartingTile});

		for (int i = 1; i < range + 1; i++)
		{
			Fringes.Add({});
			//for (int k = 0; k < Fringes[i-1].Num(); k++)
			for(AUnitTile* Tile : Fringes[i-1])
			{
				for (int dir = 0; dir < 6; dir++)
				{
					AUnitTile* Neighbor = GetNeighbor(Tile->GetCoordinates(), Directions[dir]);
					if (Neighbor == NULL || Neighbor->GetOccupyingUnit() != NULL)
					{
						continue;
					}

					//
					int MovementCost = Filter.Contains(Neighbor->TerrainType) ? Filter[Neighbor->TerrainType] : Neighbor->GetMovementCost();
					int RemainingMove = VisitedTiles[Tile] - MovementCost;
					/*if (Neighbor->TerrainType == ETerrainType::Forest)
					{
						StoneSoldiersHelperFunctions::LogEngineMessage(FString("Forest: ") + FString::FromInt(MovementCost));
					}*/


					if (VisitedTiles.Contains(Neighbor) && RemainingMove > VisitedTiles[Neighbor])
					{
						VisitedTiles[Neighbor] = RemainingMove;
					}
					else if (!VisitedTiles.Contains(Neighbor) && RemainingMove >= 0)
					{
						VisitedTiles.Add(Neighbor, RemainingMove);
						MoveableTiles.Add(Neighbor);
						Neighbor->ShowMoveable();
						Fringes[i].Add(Neighbor);
					}
				}
				
			}
		}
	}

	
    return true;
}
