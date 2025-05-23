// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseUnitAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UBaseUnitAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

protected:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
private:
};
