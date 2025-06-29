/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "PlayerControllers/StoneSoldiersPlayerController.h"

void AStoneSoldiersPlayerController::OnPlayerStateChangedCallback(EPlayerState NewStateName)
{
    
}

bool AStoneSoldiersPlayerController::SwapToGameplayInteractionOptionsUI()
{
    return true;
}

bool AStoneSoldiersPlayerController::SwapToDefaultInGameUI()
{
    return true;
}

void AStoneSoldiersPlayerController::AddControlledUnit(ABaseUnit* Unit)
{
    if (Unit)
    {
        ControlledUnits.Add(Unit);
    }
}

void AStoneSoldiersPlayerController::RemoveControlledUnit(class ABaseUnit* Unit)
{
    if (ControlledUnits.Contains(Unit))
    {
        ControlledUnits.Remove(Unit);
    }

    ControlledUnits.RemoveAll([](const TObjectPtr<ABaseUnit>& Unit)
    {
        return Unit == nullptr;
    });
}

void AStoneSoldiersPlayerController::SetControlledUnits(const TArray<ABaseUnit*>& Units)
{
    ControlledUnits = Units;
}

void AStoneSoldiersPlayerController::BeginPlay()
{   
    Super::BeginPlay();
}
