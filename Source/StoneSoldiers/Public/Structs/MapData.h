// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "MapData.generated.h"

//USTRUCT()
//struct FMapTileData
//{
//	GENERATED_BODY()
//
//public:
//	FString TileType;
//
//	FVector Coordinates;
//};



USTRUCT()
struct FMapData
{
	GENERATED_BODY()

public:
	void AddData(TSharedPtr<FJsonObject> Data);

	UPROPERTY()
	int Height;

	UPROPERTY()
	int Width;

	UPROPERTY()
	TMap<FVector, int> TileData;

	FMapData() :
		Height(0),
		Width(0) {}
};


/**
 * 
 */
class STONESOLDIERS_API MapData
{
public:
	MapData();
	~MapData();
};
