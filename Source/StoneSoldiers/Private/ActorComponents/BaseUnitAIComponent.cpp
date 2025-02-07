// ©Van Phan


#include "ActorComponents/BaseUnitAIComponent.h"
#include "ActorComponents/BaseActionComponent.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameStates/StoneSoldiersGameState.h"

// Sets default values for this component's properties
UBaseUnitAIComponent::UBaseUnitAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseUnitAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...


}


// Called every frame
void UBaseUnitAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseUnitAIComponent::Init(ABaseUnit* Unit)
{
	OwningUnit = Unit;
	UnitStance = EUnitAIStance::Standard;

	UWorld* World = GetWorld();
	GameState = Cast<AStoneSoldiersGameState>(World->GetGameState());
}

/// <summary>
/// Runs the unit's behavior, calculating a tile to move to and an action to take.
/// </summary>
/// <param name="TargetMoveCoord">A reference to a Vector where we want to store the coordinates the unit should move to</param>
/// <param name="ActionComponent">A reference to a pointer to an ActionComponent where we want to store the action the unit will take</param>
void UBaseUnitAIComponent::RunUnit()
{
}

/// <summary>
/// Runs the desired behavior based on the current stance of the unit. Overriden by child classes where the delegate will be added
/// </summary>
/// <param name="Stance">The stance of the unit, used to determine what behavior the unit should take</param>
void UBaseUnitAIComponent::GetBehavior(EUnitAIStance Stance)
{
	ActiveBehaviorDelegate.RemoveAll(this);
}