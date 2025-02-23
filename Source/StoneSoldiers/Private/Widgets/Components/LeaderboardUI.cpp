// ©Van Phan


#include "Widgets/Components/LeaderboardUI.h"
#include "Components/Button.h"

bool ULeaderboardUI::Initialize()
{
    if(!Super::Initialize()) return false;

    if(BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked);
    }

    return true;
}
void ULeaderboardUI::OnButtonClicked()
{
    OnBackButtonClickedLeaderboard.Broadcast();
}