// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/BaseActionComponent.h"
#include "CombatAction.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UCombatAction : public UBaseActionComponent
{
	GENERATED_BODY()
	

public:
	virtual void UseAction(ABaseUnit* Target = nullptr) override;


};
