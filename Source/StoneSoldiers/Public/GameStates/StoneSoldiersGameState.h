// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Actors/CursorIndicator.h" // Required for weak obj ptr
#include "Actors/MovementVisualSpline.h"
#include "GameFramework/GameStateBase.h"
#include "StoneSoldiersGameState.generated.h"

UENUM(BlueprintType) 
enum class EPlayerID : uint8
{
	Player1 UMETA(DisplayName = "Player 1"),
	Player2 UMETA(DisplayName = "Player 2"),
	Player3 UMETA(DisplayName = "Player 3"),
	Player4 UMETA(DisplayName = "Player 4"),
	Player5 UMETA(DisplayName = "Player 5"),
	Player6 UMETA(DisplayName = "Player 6"),
	Player7 UMETA(DisplayName = "Player 7"),
	Player8 UMETA(DisplayName = "Player 8")
};

UENUM(BlueprintType)
enum class ETeamID : uint8
{
	Team1 UMETA(DisplayName = "Team 1"),
	Team2 UMETA(DisplayName = "Team 2"),
	Team3 UMETA(DisplayName = "Team 3"),
	Team4 UMETA(DisplayName = "Team 4")
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

	TMap<EPlayerID, TArray<TWeakObjectPtr<ABaseUnit>>> PlayerUnits;
	TMap<ETeamID, TArray<TWeakObjectPtr<ABaseUnit>>> TeamUnits;

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
	void UnitTurnStarted(class ABaseUnit* Unit);

	UFUNCTION()
	void UnitTurnFinished(class ABaseUnit* Unit);

	void SetCachedCursor(ACursorIndicator* NewCursor){ if (NewCursor) PlayerCursor = PlayerCursor = TWeakObjectPtr<ACursorIndicator>(NewCursor); }
	void SetCachedMovementVisualSpline(AMovementVisualSpline* NewSplineObj){ if (NewSplineObj) PlayerMovementVisualSpline = TWeakObjectPtr<AMovementVisualSpline>(NewSplineObj); }

	//ABaseUnit* CreateUnit(AUnitTile* TileActor, FString FactionKey, FName UnitName);

	TWeakObjectPtr<class AUnitTile> SelectedTile;
	TWeakObjectPtr<class ABaseUnit> ActiveUnit;

protected: 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

private:

	TWeakObjectPtr<ACursorIndicator> PlayerCursor;
	TWeakObjectPtr<AMovementVisualSpline> PlayerMovementVisualSpline;
	
	TArray<FName> TerrainNames = TArray<FName>{ FName("Grass"), FName("Forest"), FName("Mud"), FName("ShallowWater"), FName("DeepWater"), FName("Mountain"), FName("Lava"), FName("Blank") };
public:
	FORCEINLINE class ACursorIndicator* GetCursorIndicator() const { return PlayerCursor.Get(); }
	FORCEINLINE class AMovementVisualSpline* GetMovementSpline() const { return PlayerMovementVisualSpline.Get(); }
};
