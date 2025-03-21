// ©Van Phan

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ETerrainType : uint8
{
	Grass,
	Forest,
	Mud,
	ShallowWater,
	DeepWater,
	Mountain,
	Lava,
	Blank
};


/**
 * 
 */
class STONESOLDIERS_API TerrainTypeEnum
{
public:
	TerrainTypeEnum();
	~TerrainTypeEnum();
};
