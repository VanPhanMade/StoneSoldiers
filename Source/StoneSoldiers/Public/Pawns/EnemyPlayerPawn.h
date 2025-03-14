// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Structs/UnitData.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "Pawns/PlayerPawn.h"
#include "EnemyPlayerPawn.generated.h"

class ABaseUnit;

UCLASS()
class STONESOLDIERS_API AEnemyPlayerPawn : public APlayerPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPlayerPawn();

	

	virtual void StartPlayerTurn() override;

	EPlayerID ID = EPlayerID::Player2;

	ETeamID TeamID = ETeamID::Team2;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Functions
	// Spawns unit from the unit data
	void SpawnUnits();

	// Places units on the map
	void PlaceUnits();

	// Sorts UnitToActivate based on activation priority
	TArray<ABaseUnit*> SortUnits();

	// Activates the provided unit, moving and picking an action
	void ActivateUnit(ABaseUnit* ActiveUnit);

	UPROPERTY(EditAnywhere)
	TArray<FUnitData> SelectedUnitData;

	UPROPERTY(EditAnywhere)
	TArray<FVector> StartingPositions;

	TArray<ABaseUnit*> UnitsToActivate;

	TArray<ABaseUnit*> ControlledUnits;


};
