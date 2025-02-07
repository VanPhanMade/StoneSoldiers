// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/BaseUnitAIComponent.h"
#include "TestAIComponent.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UTestAIComponent : public UBaseUnitAIComponent
{
	GENERATED_BODY()
	
public:
	virtual void RunUnit() override;

private:
	virtual void GetBehavior(EUnitAIStance Stance) override;

	void StationaryBehavior();

	void StandardBehavior();

	void MoveAtNearest();

	void ManageAttackAction();
};
