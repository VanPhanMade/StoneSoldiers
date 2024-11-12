// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"
#include "Widgets/CampaignOptions.h"
#include "Widgets/BattlesOptions.h"

bool UMainMenu::Initialize()
{
    if(!Super::Initialize()) return false;

    if(CampaignButton && BattlesButton && SettingsButton && ExitButton && SessionsBackToMenuButton && SettingsBackToMenuButton)
    {
        CampaignButton->OnClicked.AddDynamic(this, &ThisClass::OpenCampaignOptions);
        BattlesButton->OnClicked.AddDynamic(this, &ThisClass::OpenBattlesOptions);
        SettingsButton->OnClicked.AddDynamic(this, &ThisClass::GoToSettings);
        ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitGame);
        SessionsBackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::GoToMainMenu);
        SettingsBackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::GoToMainMenu);
    }

    if(BattleOptions)
    {
        BattleOptions->MainMenuWidget = this;
    }
    if(CampaignOptions)
    {
        CampaignOptions->MainMenuWidget = this;
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
    }
}

void UMainMenu::OpenBattlesOptions()
{
    if(BattleOptions && CampaignOptions)
    {
        CampaignOptions->SetVisibility(ESlateVisibility::Collapsed);
        BattleOptions->SetVisibility(ESlateVisibility::Visible);
    }
}

void UMainMenu::GoToSettings()
{
    if(BattleOptions && CampaignOptions)
    {
        CampaignOptions->SetVisibility(ESlateVisibility::Collapsed);
        BattleOptions->SetVisibility(ESlateVisibility::Collapsed);
    }
    if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(3);
}

void UMainMenu::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
