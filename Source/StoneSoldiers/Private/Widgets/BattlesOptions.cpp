/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/BattlesOptions.h"
#include "Components/Button.h"
#include "Widgets/MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

bool UBattlesOptions::Initialize()
{
    if(!Super::Initialize()) return false;
    if(CustomBattlesButton && MultiplayerBattlesButton && LeaderboardsButton && ReplaysButton)
    {
        CustomBattlesButton->OnClicked.AddDynamic(this, &ThisClass::OpenCustomBattles);
        MultiplayerBattlesButton->OnClicked.AddDynamic(this, &ThisClass::OpenMultiplayerBattles);
        LeaderboardsButton->OnClicked.AddDynamic(this, &ThisClass::OpenLeaderboard);
        ReplaysButton->OnClicked.AddDynamic(this, &ThisClass::OpenReplays);
    }

    SetVisibility(ESlateVisibility::Collapsed);
    return true;

}
void UBattlesOptions::OpenCustomBattles()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName("UnitSelectionSingleplayer"));
}

void UBattlesOptions::OpenMultiplayerBattles()
{
    if(MainMenuWidget)
    {
        MainMenuWidget->WidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

void UBattlesOptions::OpenLeaderboard()
{
    if(MainMenuWidget)
    {
        MainMenuWidget->WidgetSwitcher->SetActiveWidgetIndex(3);
    }
}

void UBattlesOptions::OpenReplays()
{
    if(MainMenuWidget)
    {
        MainMenuWidget->WidgetSwitcher->SetActiveWidgetIndex(4);
    }
}
