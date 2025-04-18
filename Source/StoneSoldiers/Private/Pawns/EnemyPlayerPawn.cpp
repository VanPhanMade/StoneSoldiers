/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/

#include "Pawns/EnemyPlayerPawn.h"
#include "Actors/BaseUnit.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "ActorComponents/BaseUnitAIComponent.h"
#include "PlayerControllers/CustomBattlesAIPlayerController.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"


AEnemyPlayerPawn::AEnemyPlayerPawn()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority() && !Controller)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        CachedController = GetWorld()->SpawnActor<ACustomBattlesAIPlayerController>( ControllerClass, GetActorLocation(), GetActorRotation(), SpawnParams);
        if (CachedController)
        {
            CachedController->Possess(this);
            for (const TWeakObjectPtr<ABaseUnit>& WeakUnit : ControlledUnits)
            {
                if (WeakUnit.IsValid()) 
                {
                    CachedController->AddControlledUnit(WeakUnit.Get());
                    if (!WeakUnit.Get()->OnUnitDeathDelegate.IsAlreadyBound(this, &ThisClass::DestroyUnit))
                    {
                        WeakUnit.Get()->OnUnitDeathDelegate.AddDynamic(this, &ThisClass::DestroyUnit);
                    }
                }
            }
        }
        else
        {
            StoneSoldiersHelperFunctions::LogEngineMessage("Failed to attach controller to AI! | AEnemyPlayerPawn | BeginPlay");
            return;
        }
    }

    if (UWorld* World = GetWorld())
    {
        if (AStoneSoldiersGameState* GS = World->GetGameState<AStoneSoldiersGameState>())
        {
            if (GS->PlayersInGame.Num() == GS->NumPlayers )
            {
                GS->NextPlayerTurn();
            }
        }
    }
}

void AEnemyPlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEnemyPlayerPawn::SpawnUnits()
{
    Super::SpawnUnits();
}

void AEnemyPlayerPawn::PlaceUnits()
{
    Super::PlaceUnits();
}

void AEnemyPlayerPawn::DestroyUnit(class ABaseUnit* Unit)
{
    Super::DestroyUnit(Unit);
    if (AStoneSoldiersPlayerController* PC = Cast<AStoneSoldiersPlayerController>(GetController()))
    {
       PC->RemoveControlledUnit(Unit);
    }
}

void AEnemyPlayerPawn::StartPlayerTurn()
{
    // For AI, currently just goes through all units and fires next turn logic when all units are finished acting
    UWorld* World = GetWorld();
    AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();
    
    UnitsToActivate = ControlledUnits;
    while (UnitsToActivate.Num() > 0)
    {
        if (UnitsToActivate[0].IsValid())
        {
            GameState->UnitTurnStarted(UnitsToActivate[0].Get());
            ActivateUnit(UnitsToActivate[0].Get());
        }
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
    ActiveUnit->AIComponent->RunUnit();
    ActiveUnit->EndTurn();
}