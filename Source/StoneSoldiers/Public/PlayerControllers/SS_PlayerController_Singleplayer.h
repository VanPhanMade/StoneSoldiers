// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SS_PlayerController_Singleplayer.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API ASS_PlayerController_Singleplayer : public APlayerController
{
	GENERATED_BODY()

public:
	virtual bool SwapToGameplayInteractionOptionsUI();
	virtual bool SwapToDefaultInGameUI();
 
protected: 
	virtual void BeginPlay() override;
 
private:
	UPROPERTY(EditAnywhere, Category="UI", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class UInGameHud_Singleplayer> InGameHUDWidget;

	class UInGameHud_Singleplayer* InGameHUDRef;
	
};
