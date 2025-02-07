// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackButtonClickedLeaderboard); 

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API ULeaderboardUI : public UUserWidget
{
	GENERATED_BODY()

public: 
	FOnBackButtonClickedLeaderboard OnBackButtonClickedLeaderboard;
 
protected: 
	virtual bool Initialize() override;
 
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* BackButton;

	UFUNCTION()
	void OnButtonClicked();
};
