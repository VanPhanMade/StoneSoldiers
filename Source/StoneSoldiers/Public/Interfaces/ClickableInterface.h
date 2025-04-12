#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClickableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UClickableInterface : public UInterface
{
    GENERATED_BODY()
};

class STONESOLDIERS_API IClickableInterface
{
	GENERATED_BODY()

public:
	virtual void OnLeftClick(AActor* InstigatorActor) = 0;
	virtual void OnRightClick(AActor* InstigatorActor) = 0;
};
