// ©Van Phan


#include "Widgets/Components/ReplaysUI.h"
#include "Components/Button.h"

bool UReplaysUI::Initialize()
{
    if(!Super::Initialize()) return false;

    if(BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked);
    }

    return true;
}
void UReplaysUI::OnButtonClicked()
{
    OnBackButtonClickedReplays.Broadcast();
}
