// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PreBattleOptions.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UPreBattleOptions : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool SetParentHUD(class UUserWidget* Parent);

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void StartFight();

private:
	UPROPERTY(EditAnywhere)
	class UInGameHud_Singleplayer* ParentHUD;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartFightButton;

	
};
