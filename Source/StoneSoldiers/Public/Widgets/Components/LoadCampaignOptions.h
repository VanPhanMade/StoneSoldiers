// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadCampaignOptions.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackButtonClickedLoadCampaignOptions); 
/**
 * 
 */
UCLASS()
class STONESOLDIERS_API ULoadCampaignOptions : public UUserWidget
{
	GENERATED_BODY()

public: 
	FOnBackButtonClickedLoadCampaignOptions OnBackButtonClickedLoadCampaignOptions;
 
protected: 
	virtual bool Initialize() override;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* LoadButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* DeleteButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* CancelButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* LocalButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UButton* CloudButton;

	UFUNCTION()
	void BackButtonClicked();
	
};
