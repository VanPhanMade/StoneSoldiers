// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetCursorAndItemDisplay.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UWidgetCursorAndItemDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool DisplayOneUnitData();
	virtual bool DisplayTwoUnitFightingData();
	
protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;
};
