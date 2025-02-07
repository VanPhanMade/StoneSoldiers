// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitSelectionCampaignUI.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UUnitSelectionCampaignUI : public UUserWidget
{
	GENERATED_BODY()
	
public: 
 
protected: 
	virtual bool Initialize() override;
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* GoToCampaignLevelButton;

	UFUNCTION()
	void TravelToCampaignLevel();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* BackToMainMenuButton;

	UFUNCTION()
	void GoBackToMainMenu();

};
