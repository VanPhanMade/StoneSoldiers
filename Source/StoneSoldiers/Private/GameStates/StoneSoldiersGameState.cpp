// ©Van Phan


#include "GameStates/StoneSoldiersGameState.h"
#include "Net/UnrealNetwork.h"
#include "Actors/TileMap.h"
#include "Actors/UnitTile.h"
#include "Actors/BaseUnit.h"
#include "Enums/TerrainTypeEnum.h"
#include "Structs/UnitData.h"

void AStoneSoldiersGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AStoneSoldiersGameState, TileMap);
}

void AStoneSoldiersGameState::BeginPlay()
{
    Super::BeginPlay();
}

void AStoneSoldiersGameState::UnitTurnStarted(ABaseUnit* Unit)
{
    ActiveUnit = Unit;
    ActiveUnit->OnTurnFinishedDelegate.AddDynamic(this, &AStoneSoldiersGameState::UnitTurnFinished);
}

void AStoneSoldiersGameState::UnitTurnFinished(ABaseUnit* Unit)
{
    ActiveUnit->OnTurnFinishedDelegate.RemoveDynamic(this, &AStoneSoldiersGameState::UnitTurnFinished);
    ActiveUnit = nullptr;
}

void AStoneSoldiersGameState::AddTileMap(AActor* TileMapActor)
{
    if (TileMap == nullptr)
    {
        if (ATileMap* TileMapCheck = Cast<ATileMap>(TileMapActor))
        {
            TileMap = TileMapCheck;
        }
    }
}

void AStoneSoldiersGameState::AddTiles(AActor* TileActor, FVector CoordinateIndex)
{

    if (AUnitTile* Tile = Cast<AUnitTile>(TileActor))
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

        Tile->SetGameState(this);
        Tile->Init();
    }

}

void AStoneSoldiersGameState::PlaceUnit(ABaseUnit* UnitToPlace, FVector TileCoords)
{
    AUnitTile* TargetTile = Tiles[TileCoords];
    TargetTile->SetOccupyingUnit(UnitToPlace);
    UnitToPlace->SetActorLocation(TargetTile->GetHoverMeshLoc());
    UnitToPlace->TileCoords = TileCoords;
}

void AStoneSoldiersGameState::MoveUnit(AUnitTile* TargetTile)
{
    //ABaseUnit* MovingUnit = SelectedTile->GetOccupyingUnit();
    AUnitTile* PrevTile = Tiles[ActiveUnit->TileCoords];
    ActiveUnit->OnBeginMoveDelegate.Broadcast();

    if (TargetTile != PrevTile)
    {
        // Moves the Unit
        TargetTile->SetOccupyingUnit(ActiveUnit);
        ActiveUnit->SetActorLocation(TargetTile->GetHoverMeshLoc());
        PrevTile->SetOccupyingUnit(NULL);
        ActiveUnit->TileCoords = TargetTile->GetCoordinates();
    }

    //SelectedTile = NULL;
    TileMap->ClearMoveableTiles();

    // Continues with the unit's turn
    ActiveUnit->ProcessTurn();
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
