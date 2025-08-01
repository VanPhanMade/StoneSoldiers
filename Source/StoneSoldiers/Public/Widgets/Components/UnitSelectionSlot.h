// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UnitData.h"
#include "FMODEvent.h"
#include "UnitSelectionSlot.generated.h"



/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UUnitSelectionSlot : public UUserWidget
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditAnywhere)
		TEnumAsByte<EUnitType> SlotType;

		UPROPERTY(EditAnywhere)
		UFMODEvent* DropEvent;

	protected:
		virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	private:
		UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
		class UImage* UnitSlot;



	
};
