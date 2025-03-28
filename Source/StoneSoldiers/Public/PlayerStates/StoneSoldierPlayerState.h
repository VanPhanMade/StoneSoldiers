// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "StoneSoldierPlayerState.generated.h"

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
protected:
	virtual void BeginPlay() override;
private:
	FPlayerInGameStates* CurrentState;
	TArray<FPlayerInGameStates*> AllStates;
	TArray<FPlayerInGameStates*> StateStack;
public:
	FORCEINLINE FPlayerInGameStates* GetCurrenState() const { return CurrentState; }
};
