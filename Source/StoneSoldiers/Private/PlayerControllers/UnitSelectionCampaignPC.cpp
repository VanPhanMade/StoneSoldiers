/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "PlayerControllers/UnitSelectionCampaignPC.h"
#include "Widgets/UnitSelectionCampaignUI.h"

void AUnitSelectionCampaignPC::BeginPlay()
{
    if(IsLocalController() && UnitSelectionWidget)
    {
        if(UWorld* World = GetWorld())
        {
            UnitSelectionRef = CreateWidget<UUnitSelectionCampaignUI>(World, UnitSelectionWidget);
            if(UnitSelectionRef) 
            {
                UnitSelectionRef->AddToViewport();
            }
            
            // Set input mode to UI only
            FInputModeUIOnly InputModeData;
            InputModeData.SetWidgetToFocus(UnitSelectionRef->TakeWidget()); // Set the widget to focus
            InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            SetInputMode(InputModeData);

            // Show the mouse cursor
            bShowMouseCursor = true;

        }
    }
}