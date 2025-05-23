/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/UnitSelectionChoice.h"
#include "Widgets/Components/UnitSelectionDragVisual.h"
#include "Widgets/UnitDragDropOperation.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "TimerManager.h"

FReply UUnitSelectionChoice::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
    
    if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        const double CurrentClickTime = FPlatformTime::Seconds();
        if (CurrentClickTime - LastClickTime <= DoubleClickThreshold)
        {
            OnDoubleClick(InGeometry, InMouseEvent);
        }
        LastClickTime = CurrentClickTime;

        return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }
    return Reply.Unhandled();
}

void UUnitSelectionChoice::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    // Create visual to drag around
    const TObjectPtr<UUnitSelectionDragVisual> DragVisual = CreateWidget<UUnitSelectionDragVisual>(this, DragVisualWidget);
    if (!DragVisual)
    {
        StoneSoldiersHelperFunctions::LogEngineMessage("Failed to create DragVisual. Ensure DragVisualWidget is a valid UUserWidget subclass.");
        return;
    }
    else
    {
        if(UIData.PanelImage)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(UIData.PanelImage);
            DragVisual->DragVisualImage->SetBrush(Brush);
        }
        else
        {
            StoneSoldiersHelperFunctions::LogEngineMessage("No unit visual so creating generic drag visual.");
        }
        
    }

    // Assign drag data
    UUnitDragDropOperation* DragOperation = NewObject<UUnitDragDropOperation>();
    DragOperation->IncomingUIData = UIData;
    DragOperation->IncomingType = Type;
    DragOperation->IncomingRowOption = RowOption;
    DragOperation->DefaultDragVisual = DragVisual;
    DragOperation->Pivot = EDragPivot::TopLeft;

    OutOperation = DragOperation;
}

void UUnitSelectionChoice::NativeConstruct()
{
    Super::NativeConstruct();
    if(UIData.PanelImage)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(UIData.PanelImage);
        UnitDisplay->SetBrush(Brush);
    }
}

void UUnitSelectionChoice::OnDoubleClick(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
    // StoneSoldiersHelperFunctions::LogEngineMessage("Double-click detected!");
}

void UUnitSelectionChoice::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

    //StoneSoldiersHelperFunctions::LogEngineMessage("Mouse entered widget!");
    if (UnitDisplay)
    {
        UnitDisplay->SetColorAndOpacity(FLinearColor::Blue);
    }
}

void UUnitSelectionChoice::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

    //StoneSoldiersHelperFunctions::LogEngineMessage("Mouse left widget!");
    if (UnitDisplay)
    {
        UnitDisplay->SetColorAndOpacity(FLinearColor::White);
    }
}
