// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/SoftObjectPtr.h"
#include "CampaignOptions.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UCampaignOptions : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UMainMenu* MainMenuWidget;

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* NewCampaignButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* LoadCampaignButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* CustomCampaignButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* SelectCampaignButton;

	UPROPERTY(EditAnywhere, Category = "Level Selection")
    TSoftObjectPtr<UWorld> FirstCampaignUnitSelectionLevel;
	
	UFUNCTION()
	void OpenNewCampaign();

	UFUNCTION()
	void LoadCampaign();

	UFUNCTION()
	void OpenCustomCampaign();

	UFUNCTION()
	void SelectCampaign();
};
