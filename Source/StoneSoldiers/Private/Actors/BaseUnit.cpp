// ©Van Phan


#include "Actors/BaseUnit.h"
#include "ActorComponents/BaseAbilityComponent.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(RootComponent);
	Model->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	CanActivate = true;
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseUnit::Init(FUnitData Data)
{
	UnitData = Data;
	Model->SetStaticMesh(UnitData.ModelAsset);
	//StoneSoldiersHelperFunctions::LogEngineMessage(UnitData.Name);

	// Creates the Abilities
	for (int i = 0; i < UnitData.UnitCoreData.Abilities.Num(); i++)
	{
		UBaseAbilityComponent* Component = Cast<UBaseAbilityComponent>(AddComponentByClass(UnitData.UnitCoreData.Abilities[i], true, FTransform(), true));
		FinishAddComponent(Component, true, FTransform());
		Component->Init(this);
		Abilities.Add(Component);

		//StoneSoldiersHelperFunctions::LogEngineMessage(UnitData.UnitCoreData.Abilities[i].GetDefaultObject()->AbilityName);
	}
}

void ABaseUnit::ProcessTurn()
{
	CanActivate = false;
	OnTurnFinishedDelegate.Broadcast(this);
}

