// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/StoneSoldiersPlayerController.h"

void AStoneSoldiersPlayerController::OnPlayerStateChangedCallback(FString NewStateName)
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

void AStoneSoldiersPlayerController::SetControlledUnits(const TArray<ABaseUnit*>& Units)
{
    ControlledUnits = Units;
}

void AStoneSoldiersPlayerController::BeginPlay()
{   
    Super::BeginPlay();
}
