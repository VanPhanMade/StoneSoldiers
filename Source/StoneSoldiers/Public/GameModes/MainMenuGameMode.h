// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public: 
	
protected: 
	virtual void PostLogin(APlayerController* NewPlayer) override;
 
private:
	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UMainMenu> MainMenuWidget;

};
