// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReplaysUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackButtonClickedReplays); 
/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UReplaysUI : public UUserWidget
{
	GENERATED_BODY()

public: 
	FOnBackButtonClickedReplays OnBackButtonClickedReplays;
 
protected: 
	virtual bool Initialize() override;
 
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* BackButton;

	UFUNCTION()
	void OnButtonClicked();
	
};
