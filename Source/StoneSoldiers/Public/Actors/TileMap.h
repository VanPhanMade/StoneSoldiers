// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/StoneSoldiersEnums.h"
#include "Enums/TerrainTypeEnum.h"
#include "TileMap.generated.h"

UCLASS()
class STONESOLDIERS_API ATileMap : public AActor
{
	GENERATED_BODY()

public:
	ATileMap();

	virtual bool CalculateMove(FVector StartingHex, int range, TMap<ETerrainType, uint8> Filter);
	virtual void ClearMoveableTiles();
	TArray<class ABaseUnit*> GetNeighboringUnits(FVector StartingHex);

	TArray<class AUnitTile*> GetRangeOfTiles(FVector StartingHex, int range, bool OnlyOccupied = true, bool IncludeSelf = false);
	TArray<class AUnitTile*> GetTargetableTiles(FVector StartingHex, int range, bool Friendly = false, bool IncludeSelf = false);

	TArray<class AUnitTile*> MoveableTiles;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ETileType> TileType = ETileType::TileTypeNONE;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget, AllowPrivateAccess = "true"))
	FVector FirstHexPosition;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> TileClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int RowBounds;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int ColumnBounds;

	void MakeTileMoveable(class AUnitTile* Tile);

	const TArray<FVector> Directions = TArray<FVector>{ FVector(1, 0, -1), FVector(1, -1, 0), FVector(0, -1, 1), FVector(-1, 0 , 1), FVector(-1, 1, 0), FVector(0, 1, -1) };
	class AUnitTile* GetNeighbor(FVector StartHex, FVector Direction);
	void BuildMap(int Rows, int Columns);

};
