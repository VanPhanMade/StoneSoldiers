// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "StoneSoldierPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChange, FString, PlayerStateName);

struct FPlayerInGameStates
{
	
public:
	FString StateName;
	TMap<FString, FPlayerInGameStates*> ChildrenStates;
	FPlayerInGameStates() : StateName(""), ChildrenStates() {}
};
/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneSoldierPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual FPlayerInGameStates* GoToStateFromCurrent(FString NewState);
	virtual FPlayerInGameStates* PopAndGoBackAState();
	virtual FPlayerInGameStates* UpdateStateForNewTurn(bool bIsThisPlayerTurn);

	FOnPlayerStateChange OnPlayerStateChange;

protected:
	virtual void BeginPlay() override;
private:
	FPlayerInGameStates* CurrentState;
	TArray<FPlayerInGameStates*> AllStates;
	TArray<FPlayerInGameStates*> StateStack;
public:
	FORCEINLINE FPlayerInGameStates* GetCurrenState() const { return CurrentState; }
};
