// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/BaseAbilityComponent.h"
#include "ChargeAbility.generated.h"

/* Charge Ability
* Description: When attacking a target which this unit was not adjacent to at the start of its turn, this unit adds three to the units strength
* 
* Supporting Functions:
*    Detect Adjacent Units (Before Movement): At the start of a unit's turn, grab all adjacent units
*    Determine If Target Is Adjacent (Before Selecting Attack Target): Before selecting a target, determine if adjacent units were adjacent prior
*/



/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UChargeAbility : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
public:
	void Init(ABaseUnit* Unit) override;

private:
	TArray<ABaseUnit*> AdjacentUnits;

	UPROPERTY()
	class AStoneSoldiersGameState* GameState;

	UFUNCTION()
	void FindAdjacentUnits();

	UFUNCTION()
	void CheckWasTargetAdjacent(ABaseUnit* Target);

	UFUNCTION()
	void ResetStrength(ABaseUnit* Unit);
};
