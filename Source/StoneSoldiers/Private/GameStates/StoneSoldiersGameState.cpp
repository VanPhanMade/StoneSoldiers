// ©Van Phan


#include "GameStates/StoneSoldiersGameState.h"
#include "Net/UnrealNetwork.h"
#include "Actors/TileMap.h"
#include "Actors/UnitTile.h"
#include "Actors/BaseUnit.h"
#include "Actors/CursorIndicator.h"
#include "Enums/TerrainTypeEnum.h"
#include "Pawns/PlayerPawn.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "PlayerStates/StoneSoldierPlayerState.h"

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
    //ActiveUnit->OnTurnFinishedDelegate.AddDynamic(this, &AStoneSoldiersGameState::UnitTurnFinished);
}

void AStoneSoldiersGameState::RegisterPlayer(EPlayerID ID, APlayerPawn* Player)
{
    PlayersInGame.Add(ID, Player);

    if (PlayersInGame.Num() == NumPlayers)
    {
        NextPlayerTurn();
    }
}

void AStoneSoldiersGameState::NextPlayerTurn()
{
    ActivePlayer = static_cast<EPlayerID>((ActivePlayer + 1) % NumPlayers);

    PlayersInGame[ActivePlayer]->StartPlayerTurn();
}

void AStoneSoldiersGameState::UnitTurnFinished(ABaseUnit* Unit)
{
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

void AStoneSoldiersGameState::AddTiles(AActor* TileActor, FVector CoordinateIndex, int TerrainType)
{

    if (AUnitTile* Tile = Cast<AUnitTile>(TileActor))
    {
        Tiles.Add(CoordinateIndex, Tile);
        Tile->SetCoords(CoordinateIndex);
        Tile->SetTileType(static_cast<ETerrainType>(TerrainType));
        Tile->SetRowName(TerrainNames[TerrainType]);

        /*if (TreeCoords.Contains(CoordinateIndex))
        {
            Tile->SetRowName(FName("Tree"));
            Tile->SetMoveCost(2);
            Tile->TerrainType = ETerrainType::Forest;
        }*/

        Tile->SetGameState(this);
        Tile->Init();
    }

}

void AStoneSoldiersGameState::PlaceUnit(ABaseUnit* UnitToPlace, FVector TileCoords)
{
    AUnitTile* TargetTile = nullptr;
    if (AUnitTile** TargetTilePtr = Tiles.Find(TileCoords)) TargetTile = *TargetTilePtr;
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage(FString::Printf(TEXT("Could not retrieve tile at coordinate from Tiles: %s | GameState | PlaceUnit"), *TileCoords.ToString()));
        return;
    }
    if (TargetTile)
    {
        TargetTile->SetOccupyingUnit(UnitToPlace);
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage(FString::Printf(TEXT("Target tile null in tiles: %s | GameState | PlaceUnit"), *TileCoords.ToString()));
        return;
    }
    if (UnitToPlace)
    {
        UnitToPlace->SetActorLocation(TargetTile->GetHoverMeshLoc());
        UnitToPlace->TileCoords = TileCoords;
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage("Unit to place is null | GameState | PlaceUnit ");
        return;
    }
}

bool AStoneSoldiersGameState::MoveUnit(AUnitTile* TargetTile)
{
    if (TargetTile == nullptr)
    {
        StoneSoldiersHelperFunctions::LogEngineMessage("Target tile nullptr | GameState | MoveUnit ");
        return false;
    }

    //ABaseUnit* MovingUnit = SelectedTile->GetOccupyingUnit();
    AUnitTile* PrevTile = Tiles[ActiveUnit->TileCoords];
    ActiveUnit->OnBeginMoveDelegate.Broadcast();

    if (TargetTile != PrevTile)
    {
        if (TargetTile->GetOccupyingUnit() != nullptr)
        {
            StoneSoldiersHelperFunctions::LogEngineMessage("Target tile occupied | GameState | MoveUnit ");
            return false;
        }

        // Moves the Unit
        TargetTile->SetOccupyingUnit(ActiveUnit);
        ActiveUnit->SetActorLocation(TargetTile->GetHoverMeshLoc());

        if (PrevTile == nullptr)
        {
            StoneSoldiersHelperFunctions::LogEngineMessage("Prev tile is null? | GameState | MoveUnit ");
            return false;
        }
        PrevTile->SetOccupyingUnit(NULL);
        ActiveUnit->TileCoords = TargetTile->GetCoordinates();
        
    }

    //SelectedTile = NULL;
    TileMap->ClearMoveableTiles();
    
    // update UI
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    AStoneSoldierPlayerState* PlayerState = PlayerController->GetPlayerState<AStoneSoldierPlayerState>();
    if (PlayerState->GetCurrenState()->StateName == "Choosing Unit Action")
    {
        // Update UI
        GetCursorIndicator()->DisplayCharacterInfo(false, false);
        GetCursorIndicator()->DisplayCursorMesh(false);
    }
    
    // Continues with the unit's turn

    
    // ActiveUnit->ProcessTurn();

    return true;
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
