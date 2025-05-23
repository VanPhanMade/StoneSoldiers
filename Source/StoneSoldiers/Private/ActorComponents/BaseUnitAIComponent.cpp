/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "ActorComponents/BaseUnitAIComponent.h"
#include "ActorComponents/BaseActionComponent.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameStates/StoneSoldiersGameState.h"

UBaseUnitAIComponent::UBaseUnitAIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBaseUnitAIComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UBaseUnitAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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