// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/StoneSoldiersPlayerController.h"
#include "Widgets/InGameHUD.h"

void AStoneSoldiersPlayerController::BeginPlay()
{   
    Super::BeginPlay();
    if(IsLocalController() && InGameHUDWidget)
    {
        InGameHUDRef = CreateWidget<UInGameHUD>(this, InGameHUDWidget);
        if(InGameHUDRef) InGameHUDRef->AddToViewport();
    }

}