// ©Van Phan


#include "ActorComponents/BaseActionComponent.h"
#include "GameStates/StoneSoldiersGameState.h"

UBaseActionComponent::UBaseActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBaseActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

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
