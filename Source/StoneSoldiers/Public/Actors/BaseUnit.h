// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "GameFramework/Actor.h"
#include "Structs/UnitData.h"
#include "Structs/WeaponData.h"
#include "Enums/TerrainTypeEnum.h"
#include "BaseUnit.generated.h"

// Forward Class Declarations
class UBaseUnitAIComponent;


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

// On Death
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitDeathSignature, ABaseUnit*, Unit);

// Unit State Enum
UENUM()
enum EUnitState : uint8
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
	ABaseUnit();

	// Class Functions
	UFUNCTION()
	void Init(const FUnitData& Data, EPlayerID Player);

	UFUNCTION()
	void EndTurn();

	UFUNCTION()
	void Attack(ABaseUnit* Target);

	UFUNCTION()
	virtual void ResolveDamage(int damage);

	// Core Unit Properties
	UPROPERTY(VisibleAnywhere)
	TMap<ETerrainType, uint8> MovementFilter = TMap<ETerrainType, uint8>();

	UPROPERTY()
	FVector TileCoords;

	EPlayerID OwningPlayer;

	EUnitState State;

	FWeaponDataStruct CurrentWeapon;
	
	UPROPERTY()
	UBaseUnitAIComponent* AIComponent;
	
	UPROPERTY()
	TArray<class UBaseAbilityComponent*> Abilities;
	
	UPROPERTY()
	TArray<class UBaseActionComponent*> Actions;

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

	UPROPERTY()
	FOnUnitDeathSignature OnUnitDeathDelegate;
	
	// Inline Functions
	FORCEINLINE FUnitData GetUnitData() const { return UnitData; }
	FORCEINLINE int GetCurrentWeaponDamage() const { return CurrentWeapon.Damage + CurrentStrength; }
	
	// Resetting Stats Functions
	FORCEINLINE void ResetStrength() { CurrentStrength = UnitData.UnitCoreData.Strength; }
	FORCEINLINE int GetStrength() const { return CurrentStrength; }
	FORCEINLINE void SetStrength(int value) { CurrentStrength = value; }
	FORCEINLINE int GetCurrentHealth() const { return CurrentHealth; }

	FORCEINLINE TMap<TEnumAsByte<EDamageTypes>, int> GetCurrentDefenses() const { return CurrentDefenses; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Unit Data
	UPROPERTY(VisibleAnywhere)
	FUnitData UnitData;

private:
	// Components
	UPROPERTY()
	USkeletalMeshComponent* Model;

	// Stats
	UPROPERTY()
	int CurrentHealth;

	UPROPERTY()
	int CurrentStrength;

	UPROPERTY()
	TMap<TEnumAsByte<EDamageTypes>, int> CurrentDefenses;
};
