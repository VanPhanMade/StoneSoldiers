// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
//#include "Actors/BaseUnit.h"
#include "StoneSoldiersGameState.generated.h"

UENUM()
enum EPlayerID : uint8
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

UENUM()
enum ETeamID : uint8
{
	Team1,
	Team2,
	Team3,
	Team4
};


/**
 * 
 */
UCLASS()
class STONESOLDIERS_API AStoneSoldiersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public: 
	// Will want to make dynamic later
	int NumPlayers = 2;

	EPlayerID ActivePlayer = EPlayerID::Player1;

	TMap<EPlayerID, class APlayerPawn*> PlayersInGame;

	TMap<EPlayerID, TArray<class ABaseUnit*>> PlayerUnits;

	TMap<ETeamID, TArray<class ABaseUnit*>> TeamUnits;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TempUnit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	class ATileMap* TileMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FVector, class AUnitTile*> Tiles;

	UPROPERTY(EditAnywhere)
	TMap<FString, UDataTable*> FactionUnitDataTables;

	void AddTileMap(AActor* TileMapActor);
	void AddTiles(AActor* TileActor, FVector CoordinateIndex, int TerrainType);
	void PlaceUnit(class ABaseUnit* UnitToPlace, FVector TargetTile);
	bool MoveUnit(class AUnitTile* TargetTile);

	UFUNCTION()
	void RegisterPlayer(EPlayerID ID, class APlayerPawn* Player);

	UFUNCTION()
	void NextPlayerTurn();

	UFUNCTION()
	void UnitTurnStarted(ABaseUnit* Unit);

	UFUNCTION()
	void UnitTurnFinished(ABaseUnit* Unit);

	UFUNCTION()
	void SetCachedCursor(class ACursorIndicator* NewCursor){ if (NewCursor) PlayerCursor = NewCursor; }
	void SetCachedMovementVisualSpline(class AMovementVisualSpline* NewSplineObj){ if (NewSplineObj) PlayerMovementVisualSpline = NewSplineObj; }

	//ABaseUnit* CreateUnit(AUnitTile* TileActor, FString FactionKey, FName UnitName);

	class AUnitTile* SelectedTile;
	class ABaseUnit* ActiveUnit;

protected: 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

private:
	// Delete Later, Im Just Doing a Rough Test
	//TArray<FVector> TreeCoords = TArray<FVector> {FVector(3.0, 3.0, -6.0), FVector(3.0, 2.0, -5.0), FVector(2.0, 3.0, -5.0), FVector(2.0, 4.0, -6.0),
													//FVector(-1.0, 6.0, -5.0), FVector(-1.0, 7.0, -6.0), FVector(-2.0, 7.0, -5.0)};

	class ACursorIndicator* PlayerCursor;
	class AMovementVisualSpline* PlayerMovementVisualSpline;

	TArray<FName> TerrainNames = TArray<FName>{ FName("Grass"), FName("Forest"), FName("Mud"), FName("ShallowWater"), FName("DeepWater"), FName("Mountain"), FName("Lava"), FName("Blank") };
public:
	FORCEINLINE class ACursorIndicator* GetCursorIndicator() const { return PlayerCursor; }
	FORCEINLINE class AMovementVisualSpline* GetMovementSpline() const { return PlayerMovementVisualSpline; }
};
