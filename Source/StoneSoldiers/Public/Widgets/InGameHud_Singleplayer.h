// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHud_Singleplayer.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UInGameHud_Singleplayer : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool GoToPreBattleOptions();
	virtual bool GoToMainInGameOverlay();
	virtual bool GoToGameplayInteractionOptions();

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY( meta = (BindWidget))
	class UPreBattleOptions* PreBattleOptions;

	UPROPERTY( meta = (BindWidget))
	class UGameplayInteractionOptions* GameplayInteractionOptions;
	
};
