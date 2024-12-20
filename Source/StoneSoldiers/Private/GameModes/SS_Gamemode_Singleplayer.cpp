// ©Van Phan


#include "GameModes/SS_Gamemode_Singleplayer.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Actors/BaseUnit.h"
#include "Actors/StoneCasterUnit.h"
#include "Actors/GolemUnit.h"

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
}