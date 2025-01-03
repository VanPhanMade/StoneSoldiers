// ©Van Phan


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