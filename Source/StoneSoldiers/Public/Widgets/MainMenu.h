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
	UFUNCTION()
	void GoToMainMenu();
 
protected: 
	virtual bool Initialize() override;

private:
	// Main Menu UI Elements
	UPROPERTY( meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* PlayButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* EditTeamButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* SettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* ExitButton;

	// Team Editor UI Elements
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* TeamEditorBackToMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UHorizontalBox* ArcheryRow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UHorizontalBox* FootmenRow;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UHorizontalBox* CavalryRow;

	// Game Sessions UI Elements
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* SessionsBackToMenuButton;

	

	// Settings UI Elements
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess="true"))
	class UButton* SettingsBackToMenuButton;


	UFUNCTION()
	void GoToPlayOptions();

	UFUNCTION()
	void GoToTeamEditor();
	
	UFUNCTION()
	void GoToSettings();

	UFUNCTION()
	void ExitGame();
};
