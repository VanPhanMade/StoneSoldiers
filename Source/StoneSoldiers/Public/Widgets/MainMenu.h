// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable)
	void GoToMainMenu();

	UFUNCTION()
	void GoToLoadCampaigns();

	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;
 
protected: 
	virtual bool Initialize() override;

private:
	// Main Menu UI Elements
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* CampaignButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* BattlesButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* SettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* ExitButton;

	// Settings UI Elements
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* SettingsBackToMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UBattlesOptions* BattleOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UCampaignOptions* CampaignOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UMultiplayerSessionsUI* MultiplayerSessionsUI;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class ULoadCampaignOptions* LoadCampaignOptions;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class ULeaderboardUI* LeaderboardUI;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UReplaysUI* ReplaysUI;

	UFUNCTION()
	void OpenCampaignOptions();

	UFUNCTION()
	void OpenBattlesOptions();
	
	UFUNCTION()
	void GoToSettings();

	UFUNCTION()
	void GoToReplays();

	UFUNCTION()
	void GoToLeaderboards();

	

	UFUNCTION()
	void ExitGame();
};
