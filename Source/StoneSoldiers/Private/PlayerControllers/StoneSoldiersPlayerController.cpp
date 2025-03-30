// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/StoneSoldiersPlayerController.h"

#include "Actors/CursorIndicator.h"
#include "Actors/MovementVisualSpline.h"
#include "PlayerStates/StoneSoldierPlayerState.h"
#include "Widgets/InGameHud_Singleplayer.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

void AStoneSoldiersPlayerController::OnPlayerStateChangedCallback(FString NewStateName)
{
    UWorld* World = GetWorld();
    AStoneSoldiersGameState* GS = World->GetGameState<AStoneSoldiersGameState>();
    if (GS == nullptr)
    {
        StoneSoldiersHelperFunctions::LogEngineMessage(FString::Printf(TEXT("Can't retrieve GS | ASS_PlayerController_SinglePlayer | OnPlayerStateChangedCallback")));
        return;
    }
    
    // Gets set visible in UnitTile OnTileHover
    GS->GetMovementSpline()->SetVisibilityForSpline(NewStateName == "Moving Unit" || NewStateName == "Targeting Unit Action");
    GS->GetCursorIndicator()->DisplayCharacterInfo(false, false, nullptr, nullptr); 
    
    if (NewStateName == "My Turn" || NewStateName == "Not My Turn")
    {
        SwapToDefaultInGameUI();
        GS->GetCursorIndicator()->DisplayCursorMesh(true);
        return;
    }

    if (NewStateName == "Moving Unit")
    {
        GS->GetCursorIndicator()->DisplayCursorMesh(false);
        return;
    }

    if (NewStateName == "Choosing Unit Action")
    {
        SwapToGameplayInteractionOptionsUI();
        GS->GetCursorIndicator()->DisplayCursorMesh(false);
        return;
    }

    if (NewStateName == "Targeting Unit Action")
    {
        GS->GetCursorIndicator()->DisplayCursorMesh(false);
        return;
    }

    StoneSoldiersHelperFunctions::LogEngineMessage(FString::Printf(TEXT("Improper state: %s | ASS_PlayerController_SinglePlayer | OnPlayerStateChangedCallback"), *NewStateName));
}

bool AStoneSoldiersPlayerController::SwapToGameplayInteractionOptionsUI()
{
    if (InGameHUDRef)
    {
        InGameHUDRef->GoToGameplayInteractionOptions();
        return true;
    }
    
    return false;
}

bool AStoneSoldiersPlayerController::SwapToDefaultInGameUI()
{
    if (InGameHUDRef)
    {
        InGameHUDRef->GoToMainInGameOverlay();
        return true;
    }
    return false;
}

void AStoneSoldiersPlayerController::BeginPlay()
{   
    Super::BeginPlay();
    if(IsLocalController() && InGameHUDWidget)
    {
        if(UWorld* World = GetWorld())
        {
            InGameHUDRef = CreateWidget<UInGameHud_Singleplayer>(World, InGameHUDWidget);
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

        if (AStoneSoldierPlayerState* PS = GetPlayerState<AStoneSoldierPlayerState>())
        {
            PS->OnPlayerStateChange.AddDynamic(this, &ThisClass::OnPlayerStateChangedCallback);
        }
        else
        {
            StoneSoldiersHelperFunctions::LogEngineMessage(FString::Printf(TEXT("Failed to retrieve player state | ASS_PlayerController_Singleplayer | BeginPlay")));
        }
    }

}
