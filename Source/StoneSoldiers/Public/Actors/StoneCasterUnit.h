// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseUnit.h"
#include "StoneCasterUnit.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneCasterUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AddControlledGolem(class AGolemUnit* Golem);

	FORCEINLINE int32 GetControlledNum() { return ControlledGolems.Num(); }
	
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<class AGolemUnit*> ControlledGolems;
};
