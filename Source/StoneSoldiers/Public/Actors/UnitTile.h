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



UCLASS()
class STONESOLDIERS_API AUnitTile : public AActor, public IClickableInterface, public IHoverableInterface
{
	GENERATED_BODY()
	
public:	
	AUnitTile();

	// Implement the clickable interface functions
	virtual void OnLeftClick() override;
	virtual void OnRightClick() override;

	// Implement the hoverable interface functions
	virtual void OnHoverBegin() override;
	virtual void OnHoverEnd() override; 

	virtual void Init(FVector Coords, UDataTable* Data, FName RowName);
	virtual void ShowMoveable();
	virtual AActor* SpawnUnit();

	// Temp
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	ETerrainType TerrainType;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
    UDataTable* TileVisualsDataTable;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
    FName SelectedTileRowName;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* MainMesh;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* HoverMesh;

	

	void UpdateTilesFromSelection();

	struct FTileData* TileData;

	FVector Coordinates;

	int MovementCost;

	UPROPERTY()
	ABaseUnit* OccupyingUnit = nullptr;

public: // Getters
	FORCEINLINE FVector GetCoordinates() const { return Coordinates; } 
	FORCEINLINE int GetMovementCost() const { return MovementCost; } 
	FORCEINLINE ABaseUnit* GetOccupyingUnit() const { return OccupyingUnit; }
	FORCEINLINE FVector GetHoverMeshLoc() const { return HoverMesh->GetComponentLocation(); }

	// Some of these will be deleted as information is moved into the data table
	FORCEINLINE void SetOccupyingUnit (ABaseUnit* Value) { OccupyingUnit = Value; }
	FORCEINLINE void SetCoords(FVector Value) { Coordinates = Value; }
	FORCEINLINE void SetMoveCost (int Value) { MovementCost = Value; }
	FORCEINLINE void SetRowName (FName Value) { 
		SelectedTileRowName = Value;
		TileData = TileVisualsDataTable->FindRow<FTileData>(SelectedTileRowName, TEXT("UpdateTileVisuals"));
		UpdateTilesFromSelection(); 
	}

};
