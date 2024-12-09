// ©Van Phan


#include "GameStates/StoneSoldiersGameState.h"
#include "Net/UnrealNetwork.h"
#include "Actors/TileMap.h"
#include "Actors/UnitTile.h"
#include "Actors/BaseUnit.h"
#include "Enums/TerrainTypeEnum.h"
#include "Structs/UnitData.h"

void AStoneSoldiersGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AStoneSoldiersGameState, TileMap); 
}

void AStoneSoldiersGameState::BeginPlay()
{
    Super::BeginPlay();
}

void AStoneSoldiersGameState::AddTileMap(AActor *TileMapActor)
{
    if(TileMap == nullptr)
    {
        if(ATileMap* TileMapCheck = Cast<ATileMap>(TileMapActor))
        {
            TileMap = TileMapCheck;
        }
    }
}

void AStoneSoldiersGameState::AddTiles(AActor *TileActor, FVector CoordinateIndex)
{

    if(AUnitTile* Tile = Cast<AUnitTile>(TileActor))
    {
        Tiles.Add(CoordinateIndex, Tile);
        Tile->SetCoords(CoordinateIndex);
        Tile->SetMoveCost(1);

        if (TreeCoords.Contains(CoordinateIndex))
        {
            Tile->SetRowName(FName("Tree"));
            Tile->SetMoveCost(2);
            Tile->TerrainType = ETerrainType::Forest;
        }
    }

}

void AStoneSoldiersGameState::PlaceUnit(ABaseUnit* UnitToPlace, FVector TileCoords)
{
    AUnitTile* TargetTile = Tiles[TileCoords];
    TargetTile->SetOccupyingUnit(UnitToPlace);
    UnitToPlace->SetActorLocation(TargetTile->GetHoverMeshLoc());
    UnitToPlace->SetTileCoords(TileCoords);
}

void AStoneSoldiersGameState::MoveUnit(AUnitTile* TargetTile)
{
    ABaseUnit* MovingUnit = SelectedTile->GetOccupyingUnit();

    MovingUnit->OnBeginMovement.Broadcast();
    
    if (TargetTile != SelectedTile)
    {
        // Moves the Unit
        TargetTile->SetOccupyingUnit(MovingUnit);
        MovingUnit->SetActorLocation(TargetTile->GetHoverMeshLoc());
        SelectedTile->SetOccupyingUnit(nullptr);
        MovingUnit->SetTileCoords(TargetTile->GetCoordinates());
    }

    SelectedTile = nullptr;
    TileMap->ClearMoveableTiles();

    // Continues with the unit's turn
    MovingUnit->ProcessTurn();
}

//ABaseUnit* AStoneSoldiersGameState::CreateUnit(AUnitTile* TileActor, FString FactionKey, FName UnitName)
//{
//    // Gets the Unit Data
//    FUnitData* UnitData = FactionUnitDataTables[FactionKey]->FindRow<FUnitData>(UnitName, TEXT("GET UNIT DATA"));
//
//    UWorld* World = GetWorld();
//    AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();
//    FTransform Transform = FTransform();
//    Transform.SetLocation(TileActor->GetHoverMeshLoc());
//    TileActor->SetOccupyingUnit(World->SpawnActor<ABaseUnit>(ABaseUnit::StaticClass(), Transform));
//    TileActor->GetOccupyingUnit()->Init(*UnitData);
//    return TileActor->GetOccupyingUnit();
//}
