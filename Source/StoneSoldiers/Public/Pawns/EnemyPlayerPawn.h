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
	AEnemyPlayerPawn();
	virtual void StartPlayerTurn() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Functions
	virtual void SpawnUnits() override;
	virtual void PlaceUnits() override;

	UFUNCTION()
	virtual void DestroyUnit(class ABaseUnit* Unit) override;

	// Sorts UnitToActivate based on activation priority 
	TArray<ABaseUnit*> SortUnits();

	// Moves unit and picks actions for AI
	void ActivateUnit(ABaseUnit* ActiveUnit);

	UPROPERTY(EditAnywhere, Category="Game", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class ACustomBattlesAIPlayerController> ControllerClass;
	
	TObjectPtr<ACustomBattlesAIPlayerController> CachedController;


	


};
