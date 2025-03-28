// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Structs/UnitData.h"
#include "SS_Gamemode_Singleplayer.generated.h"


/**
 * 
 */
UCLASS()
class STONESOLDIERS_API ASS_Gamemode_Singleplayer : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	class ABaseUnit* CreateUnit(FUnitData Data);

protected: 
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACursorIndicator> PlayerCursorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMovementVisualSpline> PlayerMovementVisualSplineClass;
	
};
