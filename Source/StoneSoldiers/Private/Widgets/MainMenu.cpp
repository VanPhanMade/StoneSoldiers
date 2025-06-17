/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Widgets/CampaignOptions.h"
#include "Widgets/BattlesOptions.h"
#include "Widgets/Components/MultiplayerSessionsUI.h"
#include "Widgets/Components/LoadCampaignOptions.h"
#include "Widgets/Components/LeaderboardUI.h"
#include "Widgets/Components/ReplaysUI.h"

#include "FMODBlueprintStatics.h"

bool UMainMenu::Initialize()
{
    if(!Super::Initialize()) return false;

    if(CampaignButton && BattlesButton && SettingsButton && ExitButton && SettingsBackToMenuButton)
    {
        CampaignButton->OnClicked.AddDynamic(this, &ThisClass::OpenCampaignOptions);
        BattlesButton->OnClicked.AddDynamic(this, &ThisClass::OpenBattlesOptions);
        SettingsButton->OnClicked.AddDynamic(this, &ThisClass::GoToSettings);
        ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitGame);
    }

    if(BattleOptions)
    {
        BattleOptions->MainMenuWidget = this;
    }
    if(CampaignOptions)
    {
        CampaignOptions->MainMenuWidget = this;
    }

    if(MultiplayerSessionsUI)
    {
        MultiplayerSessionsUI->OnBackButtonClicked.AddDynamic(this, &ThisClass::GoToMainMenu);
    }

    if(LoadCampaignOptions)
    {
        LoadCampaignOptions->OnBackButtonClickedLoadCampaignOptions.AddDynamic(this, &ThisClass::GoToMainMenu);
    }

    if(ReplaysUI)
    {
        ReplaysUI->OnBackButtonClickedReplays.AddDynamic(this, &ThisClass::GoToMainMenu);
    }

    if(LeaderboardUI)
    {
        LeaderboardUI->OnBackButtonClickedLeaderboard.AddDynamic(this, &ThisClass::GoToMainMenu);
    }

    return true;
}

void UMainMenu::GoToMainMenu()
{
    if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UMainMenu::OpenCampaignOptions()
{
    if(BattleOptions && CampaignOptions)
    {
        CampaignOptions->SetVisibility(ESlateVisibility::Visible);
        BattleOptions->SetVisibility(ESlateVisibility::Collapsed);
        UFMODBlueprintStatics::PlayEvent2D(this, ButtonPressEvent, true);
    }
}

void UMainMenu::OpenBattlesOptions()
{
    if(BattleOptions && CampaignOptions)
    {
        CampaignOptions->SetVisibility(ESlateVisibility::Collapsed);
        BattleOptions->SetVisibility(ESlateVisibility::Visible);
        UFMODBlueprintStatics::PlayEvent2D(this, ButtonPressEvent, true);
    }
}

void UMainMenu::GoToSettings()
{
    if(BattleOptions && CampaignOptions)
    {
        CampaignOptions->SetVisibility(ESlateVisibility::Collapsed);
        BattleOptions->SetVisibility(ESlateVisibility::Collapsed);
    }
    if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(2);
}

void UMainMenu::GoToReplays()
{
    if(ReplaysUI)
    {
        if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(4);
    }
}

void UMainMenu::GoToLeaderboards()
{
    if(LeaderboardUI)
    {
        if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(3);
    }
}

void UMainMenu::GoToLoadCampaigns()
{
    if(LoadCampaignOptions)
    {
        if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(5);
    }
}

void UMainMenu::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
