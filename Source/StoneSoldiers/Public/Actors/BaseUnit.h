// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/UnitData.h"
#include "Enums/TerrainTypeEnum.h"
#include "BaseUnit.generated.h"


// Delegates

// Passive

// Calculate Movement
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCalculateMovement);

// During Movement

// End of Movement



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnFinishedSignature, ABaseUnit*, Unit);


UCLASS()
class STONESOLDIERS_API ABaseUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseUnit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Init(FUnitData Data);

	void ProcessTurn();

	UPROPERTY()
	FOnCalculateMovement OnCalculateMovementDelegate;

	UPROPERTY()
	FOnTurnFinishedSignature OnTurnFinishedDelegate;
	
	UPROPERTY()
	bool CanActivate;

	UPROPERTY(VisibleAnywhere)
	TMap<ETerrainType, uint8> MovementFilter = TMap<ETerrainType, uint8>();

	//UPROPERTY(VisibleAnywhere)
	TArray<UBaseAbilityComponent*> Abilities;

	FORCEINLINE FUnitData GetUnitData() const { return UnitData; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	FUnitData UnitData;

private:
	UPROPERTY()
	UStaticMeshComponent* Model;
};
