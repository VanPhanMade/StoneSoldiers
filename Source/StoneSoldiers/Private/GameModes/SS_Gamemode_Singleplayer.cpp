// ©Van Phan


#include "GameModes/SS_Gamemode_Singleplayer.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Actors/BaseUnit.h"
#include "Actors/CursorIndicator.h"
#include "Actors/StoneCasterUnit.h"
#include "Actors/GolemUnit.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Actors/MovementVisualSpline.h"

ABaseUnit* ASS_Gamemode_Singleplayer::CreateUnit(FUnitData Data)
{

    UWorld* World = GetWorld();
    ABaseUnit* Unit = nullptr;

    FTransform Transform = FTransform();
    FVector Location = FVector::Zero();
    Transform.SetLocation(Location);

    switch (Data.Type)
    {
        case StoneCaster:
            Unit = World->SpawnActor<AStoneCasterUnit>(AStoneCasterUnit::StaticClass(), Transform);
            break;

        case Golem:
            Unit = World->SpawnActor<AGolemUnit>(AGolemUnit::StaticClass(), Transform);
            break;

        case Auxiliary:
            Unit = World->SpawnActor<ABaseUnit>(ABaseUnit::StaticClass(), Transform);
            break;

        default:
            break;
    }

    return Unit;
}

void ASS_Gamemode_Singleplayer::PostLogin(APlayerController *NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // Spawn and assign 3D cursor to game state, print error message upon failure
    if (PlayerCursorClass)
    {
        if (UWorld* World = GetWorld())
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = NewPlayer;
            SpawnParams.Instigator = NewPlayer->GetPawn();
            
            FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
            FRotator SpawnRotation = FRotator::ZeroRotator;

            if (ACursorIndicator* SpawnedCursor = World->SpawnActor<ACursorIndicator>(PlayerCursorClass, SpawnLocation, SpawnRotation, SpawnParams))
            {
                if (AStoneSoldiersGameState* StoneSoldiersGameStateGameState = GetWorld()->GetGameState<AStoneSoldiersGameState>())
                {
                    StoneSoldiersGameStateGameState->SetCachedCursor(SpawnedCursor);
                }
            }
            else
            {
                StoneSoldiersHelperFunctions::LogEngineMessage(TEXT("Failed to spawn cursor | SinglePlayerGameMode | PostLogin"));
            }
        }
    }

    if (PlayerMovementVisualSplineClass)
    {
        if (UWorld* World = GetWorld())
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = NewPlayer;
            SpawnParams.Instigator = NewPlayer->GetPawn();

            FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
            FRotator SpawnRotation = FRotator::ZeroRotator;
            if (AMovementVisualSpline* SpawnedSpline = World->SpawnActor<AMovementVisualSpline>(PlayerMovementVisualSplineClass, SpawnLocation, SpawnRotation, SpawnParams))
            {
                if (AStoneSoldiersGameState* StoneSoldiersGameStateGameState = GetWorld()->GetGameState<AStoneSoldiersGameState>())
                {
                    StoneSoldiersGameStateGameState->SetCachedMovementVisualSpline(SpawnedSpline);
                    StoneSoldiersGameStateGameState->GetMovementSpline()->SetVisibilityForSpline(false);
                }
            }
            else
            {
                StoneSoldiersHelperFunctions::LogEngineMessage(TEXT("Failed to spawn spline | SinglePlayerGameMode | PostLogin"));
            }
        }
    }
}