// ©Van Phan


#include "Widgets/UnitSelectionCampaignUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"

bool UUnitSelectionCampaignUI::Initialize()
{
    if(!Super::Initialize()) return false;
    if(GoToCampaignLevelButton)
    {
        if(GetWorld()->GetAuthGameMode())
        {
            GoToCampaignLevelButton->OnClicked.AddDynamic(this, &ThisClass::TravelToCampaignLevel);
        }
        else
        {
            GoToCampaignLevelButton->SetVisibility(ESlateVisibility::Collapsed);
        }
        
        
    }
    return true;
}
void UUnitSelectionCampaignUI::TravelToCampaignLevel()
{
    if(GetWorld() && GetWorld()->GetAuthGameMode())
    {
        const FString MapName = "/Game/Levels/GameLevels/FirstCampaign";
        GetWorld()->ServerTravel(MapName, true);
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage(" Server travel failed. ");
    }
}