/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/Components/UnitSelectionSlot.h"
#include "Widgets/UnitDragDropOperation.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Components/Image.h"

#include "FMODBlueprintStatics.h"

bool UUnitSelectionSlot::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
    if (const UUnitDragDropOperation* DroppedData = Cast<UUnitDragDropOperation>(InOperation))
    {
        if(DroppedData->IncomingType == SlotType)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(DroppedData->IncomingUIData.PanelImage);
            UnitSlot->SetBrush(Brush);

            UFMODBlueprintStatics::PlayEvent2D(this, DropEvent, true);

            // int32 DroppedUnitID = DroppedData->UnitID;
            // StoneSoldiersHelperFunctions::LogEngineMessage("On Drop Received with Unit ID: " + FString::FromInt(DroppedUnitID));
        }
        else
        {
            //StoneSoldiersHelperFunctions::LogEngineMessage("Unit doesn't match slot type.");
        }
        
        

        return true;
    }
    else
    {
        StoneSoldiersHelperFunctions::LogEngineMessage("Failed to retrieve Drop Operation Data");
    }
    return false;
}
