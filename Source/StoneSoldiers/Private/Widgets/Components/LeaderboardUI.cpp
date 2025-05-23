/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


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