// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "PlayerPawn.generated.h"

UCLASS()
class STONESOLDIERS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	UPROPERTY(EditDefaultsOnly)
	EPlayerID ID = EPlayerID::Player1;

	UPROPERTY(EditDefaultsOnly)
	ETeamID TeamID = ETeamID::Team1;
	
	virtual void StartPlayerTurn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void SpawnUnits();

	UFUNCTION()
	virtual void PlaceUnits();
	
	virtual void DestroyUnit(class ABaseUnit* Unit);

	UPROPERTY(EditAnywhere)
	TArray<struct FUnitData> SelectedUnitData;

	UPROPERTY(EditAnywhere)
	TArray<FVector> StartingPositions;

	TArray<TWeakObjectPtr<class ABaseUnit>> ControlledUnits;
	TArray<TWeakObjectPtr<class ABaseUnit>> UnitsToActivate;

private:	
	

};
