// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseUnit.h"
#include "GolemUnit.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AGolemUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetControllingCaster(class AStoneCasterUnit* Caster) { if (Caster != nullptr) ControllingCaster = Caster; }

protected:
	class AStoneCasterUnit* ControllingCaster;
};
