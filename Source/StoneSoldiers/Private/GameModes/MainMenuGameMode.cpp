/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "GameModes/MainMenuGameMode.h"
#include "Widgets/MainMenu.h"

void AMainMenuGameMode::PostLogin(APlayerController *NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if( UWorld* World = GetWorld())
    {
        UMainMenu* MainMenu = CreateWidget<UMainMenu>(World, MainMenuWidget);
        MainMenu->AddToViewport();
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if(PlayerController)
        {
            FInputModeUIOnly InputModeData;
            InputModeData.SetWidgetToFocus(MainMenu->TakeWidget());
            InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputModeData);
            PlayerController->SetShowMouseCursor(true);
        }
    }
}