/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/

#include "Widgets/UnitSelectionMultiplayerUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

bool UUnitSelectionMultiplayerUI::Initialize()
{
    if(!Super::Initialize()) return false;
    if(GoToMultiplayerLevelButton)
    {   
        if(GetWorld()->GetAuthGameMode())
        {
            GoToMultiplayerLevelButton->OnClicked.AddDynamic(this, &ThisClass::TravelToMultiplayerLevel);
        }
        else
        {
            GoToMultiplayerLevelButton->SetVisibility(ESlateVisibility::Collapsed);
        }
        
    }

    if(BackToMainMenuButton)
    {
        BackToMainMenuButton->OnClicked.AddDynamic(this, &ThisClass::GoBackToMainMenu);
    }

    return true;
}
void UUnitSelectionMultiplayerUI::TravelToMultiplayerLevel()
{
    if(GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const FString MapName = "/Game/Levels/GameLevels/GameLevel";
        GetWorld()->ServerTravel(MapName, true);
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage(" Server travel failed. ");
    }
}

void UUnitSelectionMultiplayerUI::GoBackToMainMenu()
{
    
}