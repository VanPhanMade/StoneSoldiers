// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/UnitData.h"
#include "UnitSelectionChoice.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UUnitSelectionChoice : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUIDataStruct UIData;

	UPROPERTY(EditAnywhere)
	FName RowOption;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EUnitType> Type;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UImage* UnitDisplay;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeConstruct() override; 
	virtual void OnDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override; 
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
private:
	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UUnitSelectionDragVisual> DragVisualWidget;

	double LastClickTime = 0.0;
    const double DoubleClickThreshold = 0.5;

	

};
