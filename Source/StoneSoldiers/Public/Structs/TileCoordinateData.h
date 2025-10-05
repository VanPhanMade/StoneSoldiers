#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TileCoordinateData.generated.h"

USTRUCT(BlueprintType)
struct FTileCoordinateData : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	int Q;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	int R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	int S;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	int E;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	int terrainType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	float normalX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	float normalY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TileCoordinateData")
	float normalZ;
};
