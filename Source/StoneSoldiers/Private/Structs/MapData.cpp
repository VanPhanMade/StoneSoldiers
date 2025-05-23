/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Structs/MapData.h"

MapData::MapData()
{
}

MapData::~MapData()
{
}



void FMapData::AddData(TSharedPtr<FJsonObject> Data)
{
	// Set Height and Width

	Height = Data->GetNumberField(StringCast<TCHAR>("H", 1));
	Width = Data->GetNumberField(StringCast<TCHAR>("W", 1));

	// Builds the Tile Type Map
	TArray<TSharedPtr<FJsonValue>> Tiles = Data->GetArrayField(StringCast<TCHAR>("Data", 4));

	for (int i = 0; i < Tiles.Num(); i++)
	{
		// Gets Object
		TSharedPtr<FJsonObject> Object = Tiles[i]->AsObject();

		// Gets Coordinates
		TArray<TSharedPtr<FJsonValue>> CoordsArray = Object->GetArrayField(StringCast<TCHAR>("CC", 2));
		FVector Coords = FVector(CoordsArray[0]->AsNumber(), CoordsArray[1]->AsNumber(), CoordsArray[2]->AsNumber());

		// Adds to Map
		TileData.Add(Coords, Object->GetNumberField(StringCast<TCHAR>("Type", 4)));
	}
}
