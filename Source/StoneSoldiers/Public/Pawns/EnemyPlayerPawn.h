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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void StartPlayerTurn() override;

	EPlayerID ID = EPlayerID::Player2;

	ETeamID TeamID = ETeamID::Team2;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
