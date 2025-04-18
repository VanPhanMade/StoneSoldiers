/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "ActorComponents/BaseActionComponent.h"
#include "GameStates/StoneSoldiersGameState.h"

UBaseActionComponent::UBaseActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBaseActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBaseActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseActionComponent::Init(ABaseUnit* Unit)
{
	OwningUnit = Unit;

	UWorld* World = GetWorld();
	GameState = Cast<AStoneSoldiersGameState>(World->GetGameState());
}

void UBaseActionComponent::UseAction(ABaseUnit* Target)
{
	
}
