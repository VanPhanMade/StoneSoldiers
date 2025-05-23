/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/

#include "Widgets/Components/PlayerFactionSelection.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UPlayerFactionSelection::Initialize()
{
    if(!Super::Initialize()) return false;

    if(RemovePlayerButton)
    {
        RemovePlayerButton->OnClicked.AddDynamic(this, &ThisClass::ToggleOpenSlotForPlayer);
    }
    if(AddPlayerButton)
    {
        AddPlayerButton->OnClicked.AddDynamic(this, &ThisClass::ToggleOpenSlotForPlayer);
    }

    if (bSinglePlayer)
    {
        ToggleOpenSlotForPlayer();
    }
    
    return true;
}
void UPlayerFactionSelection::ToggleOpenSlotForPlayer()
{
    if(WidgetSwitcher)
    {
        if(bSinglePlayerSlot)
        {
            RemovePlayerButton->SetVisibility(ESlateVisibility::Collapsed);
        }
        WidgetSwitcher->SetActiveWidgetIndex(WidgetSwitcher->GetActiveWidgetIndex() == 0 ? 1 : 0);
        bActivePlayer = !bActivePlayer; 
    }
}