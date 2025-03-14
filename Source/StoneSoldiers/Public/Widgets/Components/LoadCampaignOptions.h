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

	UFUNCTION()
	void BackButtonClicked();
	
};
