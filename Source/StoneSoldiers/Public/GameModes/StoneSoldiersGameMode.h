// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StoneSoldiersGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneSoldiersGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
private:

	
};
