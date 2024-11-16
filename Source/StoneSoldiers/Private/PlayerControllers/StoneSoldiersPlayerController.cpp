// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/StoneSoldiersPlayerController.h"
#include "Widgets/InGameHUD.h"

void AStoneSoldiersPlayerController::BeginPlay()
{   
    Super::BeginPlay();
    if(IsLocalController() && InGameHUDWidget)
    {
        if(UWorld* World = GetWorld())
        {
            InGameHUDRef = CreateWidget<UInGameHUD>(World, InGameHUDWidget);
            if(InGameHUDRef) 
            {
                InGameHUDRef->AddToViewport();
                InGameHUDRef->SetIsFocusable(false); // Prevents widget from capturing focus
            }
        }
        
        
        FInputModeGameAndUI InputMode;
        InputMode.SetHideCursorDuringCapture(false);  // Ensure cursor stays visible
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);  // Lock mouse to the viewport

        // This line ensures UI focus does not consume input exclusively
        InputMode.SetWidgetToFocus(nullptr); // Explicitly state there's no UI focus capture
        
        SetInputMode(InputMode);

        bShowMouseCursor = true;  // Show the mouse cursor
        SetIgnoreLookInput(false);  // Ensure mouse movement is applied

    }

}