// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/BaseAbilityComponent.h"
#include "Enums/TerrainTypeEnum.h"
#include "FlyingAbility.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API UFlyingAbility : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
public:
	
	UFlyingAbility();

	void Init(ABaseUnit* Unit) override;

private:
	void UseAbility() override;

	UFUNCTION()
	void CreateFilter();
	
	//UPROPERTY(VisibleAnywhere)
	TMap<ETerrainType, uint8> FlyingFilter;
};
