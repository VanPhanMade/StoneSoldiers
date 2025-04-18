/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/LoadCampaignOptions.h"
#include "Components/Button.h"

bool ULoadCampaignOptions::Initialize()
{
    if(!Super::Initialize()) return false;
    if(BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ThisClass::BackButtonClicked);
    }
    return true;
}

void ULoadCampaignOptions::BackButtonClicked() 
{
    OnBackButtonClickedLoadCampaignOptions.Broadcast();
}