// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnitSelectionMultiplayerGM.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AUnitSelectionMultiplayerGM : public AGameModeBase
{
	GENERATED_BODY()

public:

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:

	
};
