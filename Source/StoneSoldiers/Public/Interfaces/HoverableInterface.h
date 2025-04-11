#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HoverableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHoverableInterface : public UInterface
{
    GENERATED_BODY()
};

class STONESOLDIERS_API IHoverableInterface
{
	GENERATED_BODY()
	
public:
	virtual void OnHoverBegin(AActor* InstigatorActor) = 0;
	virtual void OnHoverEnd(AActor* InstigatorActor) = 0;
};
