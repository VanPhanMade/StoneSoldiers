// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayInteractionOptions.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UGameplayInteractionOptions : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitUnitInformation();
	virtual bool SetParentHUD(class UUserWidget* Parent);
	
	UFUNCTION()
	virtual void GoToAttackInteractions();
	UFUNCTION()
	virtual void InteractNearbyWorldObject();
	UFUNCTION()
	virtual void GoToSpellInteractions();
	UFUNCTION()
	virtual void GoToItemInteractions();
	UFUNCTION()
	virtual void UnitGuard();
	UFUNCTION()
	virtual void UnitWait();
	UFUNCTION()
	virtual void CancelUnitAction();
	UFUNCTION()
	virtual void ReturnToInteractionOptions();
	
protected:
	virtual bool Initialize() override;
private:
	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;
	
	UPROPERTY( meta = (BindWidget))
	class UButton* AttackButton;

	UPROPERTY( meta = (BindWidget))
	class UButton* SpellsButton;

	UPROPERTY( meta = (BindWidget))
	class UButton* ItemsButton;

	UPROPERTY( meta = (BindWidget))
	class UButton* GuardButton;

	UPROPERTY( meta = (BindWidget))
	class UButton* WaitButton;

	UPROPERTY( meta = (BindWidget))
	class UButton* InteractButton;

	UPROPERTY( meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY( meta = (BindWidget))
	class UButton* WaitButtonWorldInteraction;

	UPROPERTY( meta = (BindWidget))
	class UButton* BackButtonFromInventory;

	class UInGameHud_Singleplayer* ParentHUD;
};
