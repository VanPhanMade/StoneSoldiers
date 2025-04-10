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
	virtual void OnPlayerStateChangedCallback(FString NewStateName);
	virtual bool SwapToGameplayInteractionOptionsUI();
	virtual bool SwapToDefaultInGameUI();
	
	void AddControlledUnit(class ABaseUnit* Unit);
	void SetControlledUnits(const TArray<class ABaseUnit*>& Units);
	
protected: 
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UInGameHud_Singleplayer> InGameHUDWidget;

	UPROPERTY()
	class UInGameHud_Singleplayer* InGameHUDRef;

	TArray<class ABaseUnit*> ControlledUnits;
	
public:
	FORCEINLINE const TArray<ABaseUnit*>& GetControlledUnits() const { return ControlledUnits; }
};
