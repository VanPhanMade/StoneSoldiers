// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "GameFramework/Actor.h"
#include "Structs/UnitData.h"
#include "Structs/WeaponData.h"
#include "Enums/TerrainTypeEnum.h"
#include "BaseUnit.generated.h"


// Delegates

// Passive

// Calculate Movement
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCalculateMovement);

// During Movement
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginMovementSignature);

// End of Movement

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatTargetSigniture, ABaseUnit*, Target);

// End of Turn
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnFinishedSignature, ABaseUnit*, Unit);

// Unit State Enum
UENUM()
enum UUnitState : uint8
{
	Ready,
	Moving,
	Active,
	Finished
};

// Base Unit Class
UCLASS()
class STONESOLDIERS_API ABaseUnit : public AActor
{
	GENERATED_BODY()

public:
	// Base Functions
	// Sets default values for this actor's properties
	ABaseUnit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Class Functions
	UFUNCTION()
	void Init(FUnitData Data, UPlayerID Player);

	UFUNCTION()
	void ProcessTurn();

	UFUNCTION()
	void EndTurn();

	UFUNCTION()
	void Attack(ABaseUnit* Target);

	// Core Unit Properties
	UPROPERTY(VisibleAnywhere)
	TMap<ETerrainType, uint8> MovementFilter = TMap<ETerrainType, uint8>();

	UPROPERTY()
	FVector TileCoords;

	UPlayerID OwningPlayer;

	UUnitState State;

	FWeaponDataStruct CurrentWeapon;

	// Ability Properties
	UPROPERTY()
	TArray<class UBaseAbilityComponent*> Abilities;

	// Action Properties
	UPROPERTY()
	TArray<class AUnitTile*> ValidActionTiles;

	// Delegates
	UPROPERTY()
	FOnCalculateMovement OnCalculateMovementDelegate;

	UPROPERTY()
	FOnBeginMovementSignature OnBeginMoveDelegate;

	UPROPERTY()
	FOnCombatTargetSigniture OnCombatTargetDelegate;

	UPROPERTY()
	FOnTurnFinishedSignature OnTurnFinishedDelegate;

	// Inline Functions
	FORCEINLINE FUnitData GetUnitData() const { return UnitData; }
	
	// Reseting Stats Functions
	FORCEINLINE void ResetStrength() { CurrentStrength = UnitData.UnitCoreData.Strength; }
	FORCEINLINE int GetStrength() { return CurrentStrength; }
	FORCEINLINE void SetStrength(int value) { CurrentStrength = value; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Unit Data
	UPROPERTY(VisibleAnywhere)
	FUnitData UnitData;

private:
	// Components
	UPROPERTY()
	UStaticMeshComponent* Model;

	// Stats
	UPROPERTY()
	int CurrentHealth;

	UPROPERTY()
	int CurrentStrength;

	UPROPERTY()
	TMap<TEnumAsByte<EDamageTypes>, int> CurrentDefenses;
};
