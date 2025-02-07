// ©Van Phan


#include "Widgets/UnitSelectionSingleplayerUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Components/WidgetSwitcher.h"

bool UUnitSelectionSingleplayerUI::Initialize()
{
    if(!Super::Initialize()) return false;
    if(GoToSinglePlayerLevelButton)
    {
        if(GetWorld()->GetAuthGameMode())
        {
            if(GoToSinglePlayerLevelButton) GoToSinglePlayerLevelButton->OnClicked.AddDynamic(this, &ThisClass::TravelToSingleplayerLevel);
            if(ShowMapButton) ShowMapButton->OnClicked.AddDynamic(this, &ThisClass::ShowMapDataCallback);
            if(ShowSettingsButton) ShowSettingsButton->OnClicked.AddDynamic(this, &ThisClass::ShowSessionOptionsCallback);
            if(ShowUnitInfoButton) ShowUnitInfoButton->OnClicked.AddDynamic(this, &ThisClass::ShowUnitInfoCallback);
            if(BackToMainMenuButton) BackToMainMenuButton->OnClicked.AddDynamic(this, &ThisClass::BackToMainMenuCallback);
        }
        else
        {
            GoToSinglePlayerLevelButton->SetVisibility(ESlateVisibility::Collapsed);
        }
        
    }

    return true;
}


void UUnitSelectionSingleplayerUI::TravelToSingleplayerLevel()
{
    if(GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const FString MapName = "/Game/Levels/GameLevels/GameLevelSinglePlayer";
        GetWorld()->ServerTravel(MapName, true);
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage(" Server travel failed. ");
    }

}

void UUnitSelectionSingleplayerUI::ShowMapDataCallback()
{
    if(WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(0);
    }
}

void UUnitSelectionSingleplayerUI::ShowSessionOptionsCallback()
{
    if(WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

void UUnitSelectionSingleplayerUI::ShowUnitInfoCallback()
{
    if(WidgetSwitcher)
    {
        WidgetSwitcher->SetActiveWidgetIndex(2);
    }
}

void UUnitSelectionSingleplayerUI::BackToMainMenuCallback()
{
    if(GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const FString MapName = "/Game/Levels/MainMenu/MainMenu";
        GetWorld()->ServerTravel(MapName, true);
    }
}
