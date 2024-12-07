// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Actors/BaseUnit.h"
#include "StoneSoldiersGameState.generated.h"

/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneSoldiersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	public: 
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
		void PlaceUnit(ABaseUnit* UnitToPlace, FVector TargetTile);
		void MoveUnit(class AUnitTile* TargetTile);

		//ABaseUnit* CreateUnit(AUnitTile* TileActor, FString FactionKey, FName UnitName);

		class AUnitTile* SelectedTile;
		//ABaseUnit* StoredUnit;

	protected: 
		virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
		virtual void BeginPlay() override;

	private:
		// Delete Later, Im Just Doing a Rough Test
		TArray<FVector> TreeCoords = TArray<FVector> {FVector(3.0, 3.0, -6.0), FVector(3.0, 2.0, -5.0), FVector(2.0, 3.0, -5.0), FVector(2.0, 4.0, -6.0),
														FVector(-1.0, 6.0, -5.0), FVector(-1.0, 7.0, -6.0), FVector(-2.0, 7.0, -5.0)};

};
