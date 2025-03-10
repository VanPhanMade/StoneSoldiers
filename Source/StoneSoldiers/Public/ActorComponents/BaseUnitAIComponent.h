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
	// Sets default values for this component's properties
	UBaseUnitAIComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(class ABaseUnit* Unit);

	// Should take in a pointer to a 
	virtual void RunUnit();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FBehaviorSignature ActiveBehaviorDelegate;

	virtual void GetBehavior(EUnitAIStance Stance);

	class AStoneSoldiersGameState* GameState;

	class ABaseUnit* OwningUnit;

	EUnitAIStance UnitStance;
};
