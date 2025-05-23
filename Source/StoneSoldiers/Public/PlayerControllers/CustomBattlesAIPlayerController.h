// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "StoneSoldiersPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "CustomBattlesAIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API ACustomBattlesAIPlayerController : public AStoneSoldiersPlayerController
{
	GENERATED_BODY()
	
public:

protected:
	virtual bool SwapToGameplayInteractionOptionsUI() override;
	virtual bool SwapToDefaultInGameUI() override;
	virtual void BeginPlay() override;
private:
};
