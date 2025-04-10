// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/AIEnums.h"
#include "BaseUnitAIComponent.generated.h"

// Forward Class Declarations
class UBaseActionComponent;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorSignature, FVector, MoveCoords, UBaseActionComponent*, ActionComponent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STONESOLDIERS_API UBaseUnitAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseUnitAIComponent();

	void Init(class ABaseUnit* Unit);

	// Should take in a pointer to a 
	virtual void RunUnit();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FBehaviorSignature ActiveBehaviorDelegate;

	virtual void GetBehavior(EUnitAIStance Stance);

	class AStoneSoldiersGameState* GameState;

	class ABaseUnit* OwningUnit;

	EUnitAIStance UnitStance;
};
