// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerSessionsUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackButtonClicked); 
/**
 * 
 */

UCLASS()
class STONESOLDIERS_API UMultiplayerSessionsUI : public UUserWidget
{
	GENERATED_BODY()

public: 
	FOnBackButtonClicked OnBackButtonClicked;

	UPROPERTY(BlueprintReadOnly)
	class USessionDataUI* ActiveSessionSelected;
 
protected: 
	virtual bool Initialize() override;

	void OnFindSessions(const TArray<FOnlineSessionSearchResult> &SessionResults, bool bWasSuccessful);
 
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* FilterOnlineGamesButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* FilterLocalGamesButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* TryJoinSelectedSessionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* TrySpectateSelectedSessionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* TryHostSessionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* RefreshSessionsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* CancelHostButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* ConfirmHostButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UComboBoxString* BattleTypeSelection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UCheckBox* ShowFullGamesToggle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UCheckBox* ShowNon_FriendGamesToggle;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UCheckBox* ShowPasswordedGamesToggle;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UEditableTextBox* SessionNameTextFilterBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UScrollBox* SessionsAvailableList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UOverlay* HostSettingsOverlay;

	UFUNCTION()
	void BackButtonClicked();

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void HostConfirmButtonClicked();

	UFUNCTION()
	void HostCancelButtonClicked();

	UFUNCTION()
	void OnSessionCreatedSuccess();

	UFUNCTION()
	void OnSessionCreatedFailure();

	UFUNCTION()
	void RefreshSessionsList();

	UPROPERTY(EditAnywhere, Category = UI, meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UUserWidget> ServerSearchResultWidget;

	
};
