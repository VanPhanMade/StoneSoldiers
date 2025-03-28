// ©Van Phan


#include "PlayerControllers/SS_PlayerController_Singleplayer.h"
#include "Widgets/InGameHud_Singleplayer.h"

bool ASS_PlayerController_Singleplayer::SwapToGameplayInteractionOptionsUI()
{
    if (InGameHUDRef)
    {
        InGameHUDRef->GoToGameplayInteractionOptions();
        return true;
    }
    
    return false;
}

bool ASS_PlayerController_Singleplayer::SwapToDefaultInGameUI()
{
    if (InGameHUDRef)
    {
        InGameHUDRef->GoToMainInGameOverlay();
        return true;
    }
    return false;
}

void ASS_PlayerController_Singleplayer::BeginPlay()
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
    }

}
