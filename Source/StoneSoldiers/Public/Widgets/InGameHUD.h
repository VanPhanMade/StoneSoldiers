// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UInGameHUD : public UUserWidget
{
	GENERATED_BODY()

public: 
 
protected: 
 
private:
	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;
	
};
