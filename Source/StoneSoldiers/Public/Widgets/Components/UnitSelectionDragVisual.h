// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitSelectionDragVisual.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UUnitSelectionDragVisual : public UUserWidget
{
	GENERATED_BODY()

public: 
	UPROPERTY(BlueprintReadOnly,  meta = (BindWidget))
	class UImage* DragVisualImage;
 
protected: 
 
private:
	
};
