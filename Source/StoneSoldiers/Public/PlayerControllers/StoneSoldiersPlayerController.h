// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StoneSoldiersPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneSoldiersPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	
protected: 
	virtual void BeginPlay() override;
 
private:
	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UInGameHUD> InGameHUDWidget;

	class UInGameHUD* InGameHUDRef;

};
