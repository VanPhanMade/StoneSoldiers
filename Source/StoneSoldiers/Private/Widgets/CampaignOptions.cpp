/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/CampaignOptions.h"
#include "Components/Button.h"
#include "Widgets/MainMenu.h"
#include "Kismet/GameplayStatics.h"

bool UCampaignOptions::Initialize()
{
    if(!Super::Initialize()) return false;

    SetVisibility(ESlateVisibility::Collapsed);

    if(NewCampaignButton && LoadCampaignButton)
    {
        NewCampaignButton->OnClicked.AddDynamic(this, &ThisClass::OpenNewCampaign);
        LoadCampaignButton->OnClicked.AddDynamic(this, &ThisClass::LoadCampaign);
    }

    return true;
}


void UCampaignOptions::OpenNewCampaign()
{
    if (FirstCampaignUnitSelectionLevel.IsValid())
    {
        // Get the level name from the path
        FString LevelName = FirstCampaignUnitSelectionLevel.GetAssetName();
        
        if (!LevelName.IsEmpty())
        {
            UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
        }
    }
    else
    {
        UGameplayStatics::OpenLevel(GetWorld(), FName("UnitSelectionCampaigns"));
    }
}

void UCampaignOptions::LoadCampaign()
{
    if(MainMenuWidget)
    {
        MainMenuWidget->GoToLoadCampaigns();
    }
}
