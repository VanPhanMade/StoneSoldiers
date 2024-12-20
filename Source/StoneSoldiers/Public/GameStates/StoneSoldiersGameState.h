// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
//#include "Actors/BaseUnit.h"
#include "StoneSoldiersGameState.generated.h"

UENUM()
enum UPlayerID : uint8
{
	Player1,
	Player2,
	Player3,
	Player4,
	Player5,
	Player6,
	Player7,
	Player8
};


/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneSoldiersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	public: 
		// Will be update based on turn state later
		UPlayerID ActivePlayer = UPlayerID::Player1;


		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> TempUnit;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
		class ATileMap* TileMap;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TMap<FVector, class AUnitTile*> Tiles;

		UPROPERTY(EditAnywhere)
		TMap<FString, UDataTable*> FactionUnitDataTables;

		void AddTileMap(AActor* TileMapActor);
		void AddTiles(AActor* TileActor, FVector CoordinateIndex);
		void PlaceUnit(class ABaseUnit* UnitToPlace, FVector TargetTile);
		void MoveUnit(class AUnitTile* TargetTile);

		UFUNCTION()
		void UnitTurnStarted(ABaseUnit* Unit);

		//ABaseUnit* CreateUnit(AUnitTile* TileActor, FString FactionKey, FName UnitName);

		class AUnitTile* SelectedTile;
		class ABaseUnit* ActiveUnit;

	protected: 
		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		virtual void BeginPlay() override;

	private:
		// Delete Later, Im Just Doing a Rough Test
		TArray<FVector> TreeCoords = TArray<FVector> {FVector(3.0, 3.0, -6.0), FVector(3.0, 2.0, -5.0), FVector(2.0, 3.0, -5.0), FVector(2.0, 4.0, -6.0),
														FVector(-1.0, 6.0, -5.0), FVector(-1.0, 7.0, -6.0), FVector(-2.0, 7.0, -5.0)};

		UFUNCTION()
		void UnitTurnFinished(class ABaseUnit* Unit);

};
