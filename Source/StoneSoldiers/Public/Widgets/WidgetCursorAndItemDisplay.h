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
	virtual bool DisplayOneUnitData(const class ABaseUnit* ActiveUnit);
	virtual bool DisplayTwoUnitFightingData(const class ABaseUnit* Attacker, const class ABaseUnit* Defender);
	
protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY( meta = (BindWidget))
	class UTextBlock* ActiveUnitCurrentHealth;

	UPROPERTY( meta = (BindWidget))
	class UTextBlock* ActiveUnitMaxHealth;
};
