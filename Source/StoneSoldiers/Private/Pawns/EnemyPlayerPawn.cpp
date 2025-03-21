// ©Van Phan


#include "Pawns/EnemyPlayerPawn.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Actors/BaseUnit.h"
#include "Actors/StoneCasterUnit.h"
#include "Actors/GolemUnit.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Actors/UnitTile.h"
#include "Actors/TileMap.h"
#include "ActorComponents/BaseUnitAIComponent.h"
#include "GameModes/SS_Gamemode_Singleplayer.h"

AEnemyPlayerPawn::AEnemyPlayerPawn()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AEnemyPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
        
    SpawnUnits();
    PlaceUnits();

    UWorld* World = GetWorld();
    World->GetGameState<AStoneSoldiersGameState>()->RegisterPlayer(ID, this);
}

void AEnemyPlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AEnemyPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPlayerPawn::SpawnUnits()
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
            StoneSoldiersHelperFunctions::LogEngineMessage("Failed to retrieve unit! | AEnemyPlayerPawn | SpawnUnits");
            return;
        }
        Unit->Init(SelectedUnitData[i], ID);

        // If StoneCaster
        if (Unit->GetUnitData().Type == StoneCaster)
        {
            PreviousStoneCaster = Cast<AStoneCasterUnit>(Unit);
        }

        // If Golem
        if (Unit->GetUnitData().Type == Golem)
        {
            PreviousStoneCaster->AddControlledGolem(Cast<AGolemUnit>(Unit));
            Cast<AGolemUnit>(Unit)->SetControllingCaster(PreviousStoneCaster);
        }

        if (Unit != nullptr)
        {
            ControlledUnits.Add(Unit);
            //UnitsToActivate.Add(Unit);
            //Unit->OnTurnFinishedDelegate.AddUniqueDynamic(this, &ASS_PlayerPawn_Singleplayer::EndUnitTurn);
        }
        Unit = nullptr;
    }
}

void AEnemyPlayerPawn::PlaceUnits()
{
    UWorld* World = GetWorld();
    AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();

    for (int i = 0; i < ControlledUnits.Num(); i++)
    {
        GameState->PlaceUnit(ControlledUnits[i], StartingPositions[i]);
    }

    GameState->PlayerUnits.Add(ID, ControlledUnits);
    GameState->TeamUnits.Add(TeamID, ControlledUnits);
}

void AEnemyPlayerPawn::StartPlayerTurn()
{
    UWorld* World = GetWorld();
    AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();

    UnitsToActivate = ControlledUnits;

    /*for (ABaseUnit* UnitToReset : UnitsToActivate)
    {
        UnitToReset->State = UUnitState::Ready;
    }*/

    while (UnitsToActivate.Num() > 0)
    {
        GameState->UnitTurnStarted(UnitsToActivate[0]);
        ActivateUnit(UnitsToActivate[0]);
        UnitsToActivate.RemoveAt(0);
    }

    
    GameState->NextPlayerTurn();
}

TArray<ABaseUnit*> AEnemyPlayerPawn::SortUnits()
{
    return TArray<ABaseUnit*>();
}

void AEnemyPlayerPawn::ActivateUnit(ABaseUnit* ActiveUnit)
{
    UWorld* World = GetWorld();
    AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();
    GameState->ActiveUnit = ActiveUnit;
    
    //TArray<AUnitTile*> MoveableTiles = GameState->TileMap->CalculateMove(ActiveUnit->TileCoords, ActiveUnit->GetUnitData().UnitCoreData.Movement, ActiveUnit->MovementFilter);
    //if (MoveableTiles.Num() > 1) GameState->MoveUnit(MoveableTiles[1]);

    // Triggers the AI's Behavior
    ActiveUnit->AIComponent->RunUnit();


    ActiveUnit->EndTurn();
    GameState->ActiveUnit = nullptr;
}