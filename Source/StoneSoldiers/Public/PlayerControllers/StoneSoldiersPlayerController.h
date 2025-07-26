// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerStates/StoneSoldierPlayerState.h"
#include "StoneSoldiersPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneSoldiersPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPlayerStateChangedCallback(EPlayerState NewStateName);
	virtual bool SwapToGameplayInteractionOptionsUI();
	virtual bool SwapToDefaultInGameUI();
	
	virtual void AddControlledUnit(class ABaseUnit* Unit);
	virtual void RemoveControlledUnit(class ABaseUnit* Unit);
	virtual void SetControlledUnits(const TArray<class ABaseUnit*>& Units);
	
protected: 
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UInGameHud_Singleplayer> InGameHUDWidget;

	UPROPERTY()
	TObjectPtr<class UInGameHud_Singleplayer> InGameHUDRef;

	TArray<TObjectPtr<class ABaseUnit>> ControlledUnits;
	
public:
	FORCEINLINE TArray<TObjectPtr<class ABaseUnit>> GetControlledUnits() const { return ControlledUnits; }
};
