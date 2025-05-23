// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "StoneSoldiersPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "SS_PlayerController_Singleplayer.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API ASS_PlayerController_Singleplayer : public AStoneSoldiersPlayerController
{
	GENERATED_BODY()

public:
	virtual bool SwapToGameplayInteractionOptionsUI() override;
	virtual bool SwapToDefaultInGameUI() override;

	UFUNCTION()
	virtual void OnPlayerStateChangedCallback(FString NewStateName) override;
	virtual void BeginPlay() override;
};
