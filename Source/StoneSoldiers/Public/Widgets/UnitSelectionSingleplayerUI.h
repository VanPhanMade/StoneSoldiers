// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitSelectionSingleplayerUI.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UUnitSelectionSingleplayerUI : public UUserWidget
{
	GENERATED_BODY()

public: 
 
protected: 
	virtual bool Initialize() override;

	UFUNCTION()
	virtual void TravelToSingleplayerLevel();
	
	UFUNCTION()
	virtual void ShowMapDataCallback();

	UFUNCTION()
	virtual void ShowSessionOptionsCallback();

	UFUNCTION()
	virtual void ShowUnitInfoCallback();

	UFUNCTION()
	virtual void BackToMainMenuCallback();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* GoToSinglePlayerLevelButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UWrapBox* CasterOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UWrapBox* GolemOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UWrapBox* AuxillaryOptions;

	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* ShowMapButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* ShowSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* ShowUnitInfoButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* BackToMainMenuButton;
};
