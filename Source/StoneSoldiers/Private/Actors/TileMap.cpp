/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Actors/TileMap.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Utilities/FileSaveLoad.h"

#include "Actors/UnitTile.h"

#include <queue>
#include "Algo/Reverse.h"

#include "GameModes/SS_Gamemode_Singleplayer.h"
#include "GameModes/StoneSoldiersGameMode.h"
#include "GameStates/StoneSoldiersGameState.h"

// Struct Functions
FPathfindingNode::FPathfindingNode()
{
	f = -1;
	g = -1;
	h = -1;
}

FPathfindingNode::FPathfindingNode(int _f, int _g, int _h, FVector _parent, FVector _self)
{
	f = _f;
	g = _g;
	h = _h;
	ParentCoord = _parent;
	SelfCoord = _self;
}

const float SQRTof3 = FMath::Sqrt(3.0f);

ATileMap::ATileMap()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATileMap::BeginPlay()
{
	Super::BeginPlay();
	
	TSharedPtr<FJsonObject> MapFile = FileSaveLoad::ReadJSON(FPaths::ProjectContentDir() / TEXT("Data/MapFiles/RiverMap.json"));
	FMapData MapData = FMapData();
	MapData.AddData(MapFile);

	if(MapData.Height == 0 || MapData.Width == 0)
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Rows and columns invalid for Tile Map! | TileMap | Begin Play");
	}
	else
	{
		BuildMap(MapData);
		StoneSoldiersHelperFunctions::LogEngineMessage("This Doesn't Make Sense");
	}

}

void ATileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileMap::BuildMap(FMapData Data)
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

				for (int i = 0; i < Data.Height; i++)
				{
					for (int k = 0; k < Data.Width; k++)
					{
						// Establishes Transform
						FVector Location = FirstHexPosition;
						Location.X = Location.X + (SQRTof3 * k * 55) + (0.5 * SQRTof3 * (i % 2) * 55);
						Location.Y = Location.Y + (1.5 * i * 55);

						FQuat Quaternion = FQuat(FVector(0.0f, 0.0f, 1.0f), FMath::DegreesToRadians(30.0f));

						FTransform SpawnTransform = GetActorTransform();
						SpawnTransform.SetLocation(SpawnTransform.TransformPosition(Location));
						SpawnTransform.SetRotation(Quaternion);

						// Establishes Coordinates
						float q = k - (i - (i&1)) / 2;
						FVector CubeCoord = FVector(q, i, -q-i);
						if (FMath::IsNearlyEqual(CubeCoord.Z, 0.0f)) CubeCoord.Z = 0.0f;

						// Adds the Tile to the Game State
						GameState->AddTiles(World->SpawnActor<AUnitTile>(TileClass, SpawnTransform), CubeCoord, Data.TileData[CubeCoord]);
					}
				}
				break;

			default:
				StoneSoldiersHelperFunctions::LogEngineMessage("No valid Tile Type selected for map generation! | TileMap | BuildMap");
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
	for (AUnitTile* Tile : MoveableTiles)
	{
		Tile->UnhighlightTile();
		Tile->OnLeftClickDelegate.Clear();
		Tile->OnLeftClickDelegate.AddDynamic(Tile, &AUnitTile::ManageBaseLeftClick);
	}
	MoveableTiles.Empty();
}

TArray<ABaseUnit*> ATileMap::GetNeighboringUnits(FVector StartingHex)
{
	TArray<ABaseUnit*> NeighboringUnits;

	AStoneSoldiersGameState* GameState = GetWorld()->GetGameState<AStoneSoldiersGameState>();
	
	for (FVector const Dir : Directions)
	{
		AUnitTile* Neighbor = GetNeighbor(StartingHex, Dir);
		if (Neighbor !=nullptr && Neighbor->GetOccupyingUnit() != nullptr)
		{
			NeighboringUnits.Add(Neighbor->GetOccupyingUnit());
		}
	}

	return NeighboringUnits;
}



TArray<AUnitTile*> ATileMap::GetRangeOfTiles(FVector StartingHex, int range, bool OnlyOccupied, bool IncludeSelf)
{
	TArray<AUnitTile*> VisitedTiles;

	UWorld* World = GetWorld();
	if (AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>())
	{
		AUnitTile* StartingTile = GameState->Tiles[StartingHex];
		if (IncludeSelf)
		{
			VisitedTiles.Add(StartingTile);
			StartingTile->HighlightTile();
		}
		TArray<TArray<AUnitTile*>> Fringes;
		Fringes.Add(TArray<AUnitTile*> {StartingTile});

		for (int i = 1; i < range + 1; i++)
		{
			Fringes.Add({});
			for (AUnitTile* Tile : Fringes[i - 1])
			{
				for (int dir = 0; dir < 6; dir++)
				{
					AUnitTile* Neighbor = GetNeighbor(Tile->GetCoordinates(), Directions[dir]);
					if (Neighbor == NULL)
					{
						continue;
					}

					else if (!VisitedTiles.Contains(Neighbor))
					{
						Fringes[i].Add(Neighbor);

						if (OnlyOccupied && Neighbor->GetOccupyingUnit() == nullptr)
						{
							continue;
						}

						VisitedTiles.Add(Neighbor);
						Neighbor->HighlightTile();
					}
				}
			}
		}
	}
	
	return VisitedTiles;
}

/// <summary>
/// Gets all of the units within a certain range
/// </summary>
/// <param name="StartingHex">The coordinates of the hex to start the search from</param>
/// <param name="Range">The number of hexes away to get tiles from</param>
/// <param name="Friendly">Whether to target friendly or enemy forces. True means only target friendly, enemy means to target only enemy</param>
/// <param name"IncludeSelf"> Whether to include the starting tile or not </param>
/// <returns>All Tiles That Have a Valid Unit</returns>
TArray<class AUnitTile*> ATileMap::GetTargetableTiles(FVector StartingHex, int range, bool Friendly, bool IncludeSelf)
{
	TArray<AUnitTile*> TargetableTiles;

	UWorld* World = GetWorld();
	if (AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>())
	{
		AUnitTile* StartingTile = GameState->Tiles[StartingHex];
		if (IncludeSelf)
		{
			TargetableTiles.Add(StartingTile);
			StartingTile->HighlightTile();
		}
		TArray<TArray<AUnitTile*>> Fringes;
		Fringes.Add(TArray<AUnitTile*> {StartingTile});

		for (int i = 1; i < range + 1; i++)
		{
			Fringes.Add({});
			for (AUnitTile* Tile : Fringes[i - 1])
			{
				for (int dir = 0; dir < 6; dir++)
				{
					AUnitTile* Neighbor = GetNeighbor(Tile->GetCoordinates(), Directions[dir]);
					if (Neighbor == NULL)
					{
						continue;
					}

					else if (!TargetableTiles.Contains(Neighbor))
					{
						Fringes[i].Add(Neighbor);

						if (Neighbor->GetOccupyingUnit() == nullptr)
						{
							continue;
						}

						if (!Friendly && Neighbor->GetOccupyingUnit()->OwningPlayer == GameState->ActivePlayer)
						{
							continue;
						}

						if (Friendly && Neighbor->GetOccupyingUnit()->OwningPlayer != GameState->ActivePlayer)
						{
							continue;
						}

						TargetableTiles.Add(Neighbor);
						Neighbor->HighlightTile();
					}
				}
			}
		}
	}

	return TargetableTiles;
}

int ATileMap::GetDistanceBetweenTiles(FVector FirstTile, FVector SecondTile)
{
	//int FirstTileScalar = abs(FirstTile.X) + abs(FirstTile.Y) + abs(FirstTile.Z);
	//int SecondTileScalar = abs(SecondTile.X) + abs(SecondTile.Y) + abs(SecondTile.Z);

	//return abs((SecondTileScalar - FirstTileScalar) / 2);

	FVector SubtractedCoords = FVector(FirstTile.X - SecondTile.X, FirstTile.Y - SecondTile.Y, FirstTile.Z - SecondTile.Z);
	return (abs(SubtractedCoords.X) + abs(SubtractedCoords.Y) + abs(SubtractedCoords.Z)) / 2;
}

void ATileMap::MakeTileMoveable(AUnitTile* Tile)
{
	Tile->HighlightTile();
	Tile->OnLeftClickDelegate.Clear();
	Tile->OnLeftClickDelegate.AddDynamic(Tile, &AUnitTile::ManageMoveToTile);
}


TArray<AUnitTile*> ATileMap::CalculateMove(FVector StartingHex, int range, TMap<ETerrainType, uint8> Filter)
{
	ClearMoveableTiles();

	UWorld* World = GetWorld();
	if(AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>())
	{
		AUnitTile* StartingTile = GameState->Tiles[StartingHex];
		GameState->SelectedTile = StartingTile;
		//if (FromPlayer) MakeTileMoveable(StartingTile);

		TMap<AUnitTile*, int> VisitedTiles;
		//TArray<AUnitTile*> VisitedTiles;
		VisitedTiles.Add(StartingTile, range);
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

					if (VisitedTiles.Contains(Neighbor) && RemainingMove > VisitedTiles[Neighbor])
					{
						VisitedTiles[Neighbor] = RemainingMove;
					}
					else if (!VisitedTiles.Contains(Neighbor) && RemainingMove >= 0)
					{
						VisitedTiles.Add(Neighbor, RemainingMove);
						MoveableTiles.Add(Neighbor);
						Neighbor->HighlightTile();
						Fringes[i].Add(Neighbor);
						//MakeTileMoveable(Neighbor);
					}
				}
				
			}
		}
	}

	
    return MoveableTiles;
}


TArray<class AUnitTile*> ATileMap::GetPathToTarget(FVector StartingHex, FVector TargetHex, TMap<ETerrainType, uint8> Filter)
{
	// Initializing Lists
	std::priority_queue<FPathfindingNode, std::vector<FPathfindingNode>, std::greater<FPathfindingNode>> OpenList;
	TMap<FVector, FPathfindingNode> ClosedList;

	// Add Starting Hex
	OpenList.push(FPathfindingNode(GetDistanceBetweenTiles(StartingHex, TargetHex), 0, GetDistanceBetweenTiles(StartingHex, TargetHex), StartingHex, StartingHex));
	
	// Main Loop
	while (!OpenList.empty())
	{
		// Get Cell With Lowest F Value
		FPathfindingNode Current = OpenList.top();
		OpenList.pop();

		// Check if Current Cell Is the Goal
		if (Current.SelfCoord == TargetHex)
		{
			UWorld* World = GetWorld();
			AStoneSoldiersGameState* GameState = Cast<AStoneSoldiersGameState>(World->GetGameState());

			TArray<AUnitTile*> PathCoords;

			while (Current.SelfCoord != StartingHex)
			{
				PathCoords.Add(GameState->Tiles[Current.SelfCoord]);
				Current = ClosedList[Current.ParentCoord];
			}

			PathCoords.Add(GameState->Tiles[StartingHex]);
			Algo::Reverse(PathCoords);
			return PathCoords;
		}

		// Add the Tile to the Closed list
		ClosedList.Add(Current.SelfCoord, Current);

		// Explore All Neighbors
		for (int i = 0; i < 6; i++)
		{
			// Checks the Neighbor is in the Map
			AUnitTile* Tile = GetNeighbor(Current.SelfCoord, Directions[i]);
			if (Tile == NULL)
			{
				continue;
			}

			// Creates a new node
			FPathfindingNode Node;
			int MovementCost = Filter.Contains(Tile->TerrainType) ? Filter[Tile->TerrainType] : Tile->GetMovementCost();
			int NewG = Current.g + MovementCost;

			// Checks if the neighbor is not in the open list or has a lower g value
			if (NewG < Node.g || !ClosedList.Find(Tile->GetCoordinates()))
			{
				Node.g = NewG;
				Node.h = GetDistanceBetweenTiles(Tile->GetCoordinates(), TargetHex);
				Node.f = Node.g + Node.h;
				Node.ParentCoord = Current.SelfCoord;
				Node.SelfCoord = Tile->GetCoordinates();
				OpenList.push(Node);
			}
		}
	}

	return TArray<class AUnitTile*>();
}

AUnitTile* ATileMap::FollowPath(TArray<class AUnitTile*> Path, int MovementSpeed, TMap<ETerrainType, uint8> Filter)
{
	int RemaingingMove = MovementSpeed;

	for (int i = 0; i < Path.Num(); i++)
	{
		int MovementCost = Filter.Contains(Path[i]->TerrainType) ? Filter[Path[i]->TerrainType] : Path[i]->GetMovementCost();
		RemaingingMove -= MovementCost;

		if (RemaingingMove == 0)
		{
			return Path[i];
		}

		if (RemaingingMove < 0)
		{
			if (i == 0) return Path[0];

			return Path[i - 1];
		}
	}

	return nullptr;
}


