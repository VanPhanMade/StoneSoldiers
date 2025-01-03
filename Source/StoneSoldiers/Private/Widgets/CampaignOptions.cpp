// ©Van Phan


#include "Widgets/CampaignOptions.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UCampaignOptions::Initialize()
{
    if(!Super::Initialize()) return false;

    SetVisibility(ESlateVisibility::Collapsed);

    if(NewCampaignButton && LoadCampaignButton && CustomCampaignButton && SelectCampaignButton)
    {
        NewCampaignButton->OnClicked.AddDynamic(this, &ThisClass::OpenNewCampaign);
        LoadCampaignButton->OnClicked.AddDynamic(this, &ThisClass::LoadCampaign);
        CustomCampaignButton->OnClicked.AddDynamic(this, &ThisClass::OpenCustomCampaign);
        SelectCampaignButton->OnClicked.AddDynamic(this, &ThisClass::SelectCampaign);
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
}

void UCampaignOptions::OpenCustomCampaign()
{
}

void UCampaignOptions::SelectCampaign()
{
}
