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

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly,Category="Game")
	uint8 IncomingPlayerCount;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly,Category="Game")
	uint8 IncomingAICount;

protected: 
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ACursorIndicator> PlayerCursorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMovementVisualSpline> PlayerMovementVisualSplineClass;
	
};
