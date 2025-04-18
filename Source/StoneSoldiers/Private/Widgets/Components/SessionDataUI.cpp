/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/SessionDataUI.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Widgets/Components/MultiplayerSessionsUI.h"
#include "Components/Overlay.h"

bool USessionDataUI::Initialize()
{
    if(!Super::Initialize()) return false;

    if(HighlightBorder)
    {
        HighlightBorder->SetVisibility(ESlateVisibility::Hidden);
    }

    return true;
}

FReply USessionDataUI::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) 
{
    
    if(ParentWidget)
    {
        if(ParentWidget->ActiveSessionSelected != this && ParentWidget->ActiveSessionSelected != nullptr)
        {
            ParentWidget->ActiveSessionSelected->HighlightSessionInfoWidget(false);
            ParentWidget->ActiveSessionSelected = this;
            ParentWidget->ActiveSessionSelected->HighlightSessionInfoWidget(true);
        }
        else{
            HighlightSessionInfoWidget(true);
            ParentWidget->ActiveSessionSelected = this;
        }
        
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage("Missing parent widget");
    }
    return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
}

void USessionDataUI::HighlightSessionInfoWidget(bool bHighlight)
{
    if(HighlightBorder)
    {   
        HighlightBorder->SetVisibility(bHighlight ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}