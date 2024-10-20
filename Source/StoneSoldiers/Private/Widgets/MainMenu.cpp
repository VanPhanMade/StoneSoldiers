// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
    if(!Super::Initialize()) return false;

    if(PlayButton && SettingsButton && ExitButton && SessionsBackToMenuButton && SettingsBackToMenuButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &ThisClass::GoToPlayOptions);
        SettingsButton->OnClicked.AddDynamic(this, &ThisClass::GoToSettings);
        ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitGame);
        SessionsBackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::GoToMainMenu);
        SettingsBackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::GoToMainMenu);
    }

    return true;
}

void UMainMenu::GoToMainMenu()
{
    if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(0);
}

void UMainMenu::GoToPlayOptions()
{
    if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(1);
}

void UMainMenu::GoToSettings()
{
    if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(2);
}

void UMainMenu::ExitGame()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
