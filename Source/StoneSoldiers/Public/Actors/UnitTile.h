// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ClickableInterface.h"
#include "Interfaces/HoverableInterface.h"
#include "Structs/TileVisuals.h"
#include "GameFramework/Actor.h"
#include "Actors/BaseUnit.h"
#include "Enums/TerrainTypeEnum.h"
#include "UnitTile.generated.h"

// Interaction Delegate Signatures
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeftClickSignature, AActor*, InstigatorActor);

// Unit Tile Class
UCLASS()
class STONESOLDIERS_API AUnitTile : public AActor, public IClickableInterface, public IHoverableInterface
{
	GENERATED_BODY()

public:
	// Constructor
	AUnitTile();

	// Implement the clickable interface functions
	virtual void OnLeftClick(AActor* InstigatorActor) override;
	virtual void OnRightClick(AActor* InstigatorActor) override;

	// Implement the hoverable interface functions
	virtual void OnHoverBegin(AActor* InstigatorActor) override;
	virtual void OnHoverEnd(AActor* InstigatorActor) override;

	// Tile Selection Functions
	void HighlightTile();
	void UnhighlightTile();

	// FVector Coords, UDataTable* Data, FName RowName
	// Class Functions
	virtual void Init();
	virtual void ShowMoveable();
	virtual AActor* SpawnUnit();

	// Left Click Functions
	FOnLeftClickSignature OnLeftClickDelegate;

	UFUNCTION()
	void ManageMoveToTile(AActor* InstigatorActor);

	UFUNCTION()
	void ManageBaseLeftClick(AActor* InstigatorActor);

	UFUNCTION()
	void ManageCombat(AActor* InstigatorActor);

	// Public Tile Data
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	ETerrainType TerrainType;

	// Inline Functions
	// Getters
	FORCEINLINE FVector GetCoordinates() const { return Coordinates; }
	FORCEINLINE int GetMovementCost() const { return MovementCost; }
	FORCEINLINE ABaseUnit* GetOccupyingUnit() const { return OccupyingUnit; }
	FORCEINLINE FVector GetHoverMeshLoc() const { return HoverMesh->GetComponentLocation(); }
	//FORCEINLINE FOnLeftClickSignature GetLeftClickDelegate() const { return OnLeftClickDelegate; }

	// Setters
	// Some of these will be deleted as information is moved into the data table
	FORCEINLINE void SetOccupyingUnit(ABaseUnit* Value) { OccupyingUnit = Value; }
	FORCEINLINE void SetCoords(FVector Value) { Coordinates = Value; }
	FORCEINLINE void SetMoveCost(int Value) { MovementCost = Value; }
	FORCEINLINE void SetGameState(class AStoneSoldiersGameState* Value) { if (GameState == nullptr) GameState = Value; }
	FORCEINLINE void SetRowName(FName Value) {
		SelectedTileRowName = Value;
		TileData = TileVisualsDataTable->FindRow<FTileData>(SelectedTileRowName, TEXT("UpdateTileVisuals"));
		UpdateTilesFromSelection();
	}
	FORCEINLINE void SetTileType(ETerrainType Value) {
		TerrainType = Value;
		UpdateTileType();
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void UpdateTilesFromSelection();

	void UpdateTileType();

	// Core Tile Data
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UDataTable* TileVisualsDataTable;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName SelectedTileRowName;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HoverMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SelectionMesh;

	struct FTileData* TileData;

	// Gameplay Data
	class AStoneSoldiersGameState* GameState;

	FVector Coordinates;

	int MovementCost;

	UPROPERTY()
	ABaseUnit* OccupyingUnit = NULL;
};
