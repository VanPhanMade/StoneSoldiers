/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "ActorComponents/BaseAbilityComponent.h"

// Sets default values for this component's properties
UBaseAbilityComponent::UBaseAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBaseAbilityComponent::Init(ABaseUnit* Unit)
{
	OwningUnit = Unit;
	
	ConnectToDelegate();
}


// Called when the game starts
void UBaseAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBaseAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/// <summary>
/// Connects the Ability to the Appropriate Delegate Based On the Ability Timing
/// </summary>
void UBaseAbilityComponent::ConnectToDelegate()
{
	switch (AbilityTiming)
	{
		case EAbilityTiming::BeforeMovement:
			OwningUnit->OnCalculateMovementDelegate.AddDynamic(this, &UBaseAbilityComponent::UseAbility);
			break;

		default:
			break;
	}
}

void UBaseAbilityComponent::UseAbility()
{
}



