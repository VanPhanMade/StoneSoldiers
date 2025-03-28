// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/BaseAbilityComponent.h"
#include "BaseActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UBaseActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseActionComponent();
	
	virtual void Init(ABaseUnit* Unit);

	// UI Fields
	UPROPERTY()
	FString ActionName;

	UPROPERTY()
	UTexture2D* ActionIcon;

	// Class Fields
	ABaseUnit* OwningUnit;

	virtual void UseAction(ABaseUnit* Target = nullptr);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class AStoneSoldiersGameState* GameState;

private:
};
