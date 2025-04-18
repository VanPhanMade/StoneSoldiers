// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/TerrainTypeEnum.h"
#include "Actors/BaseUnit.h"
#include "BaseAbilityComponent.generated.h"

class ABaseUnit;


UENUM()
enum class EAbilityTiming : uint8
{
	Passive,
	BeforeMovement
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STONESOLDIERS_API UBaseAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseAbilityComponent();

	virtual void Init(ABaseUnit* Unit);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UI Fields
	UPROPERTY()
	FString AbilityName;

	UPROPERTY()
	UTexture2D* AbilityIcon;

	// Class Fields
	ABaseUnit* OwningUnit;

	EAbilityTiming AbilityTiming;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void ConnectToDelegate();
	
	virtual void UseAbility();
};
