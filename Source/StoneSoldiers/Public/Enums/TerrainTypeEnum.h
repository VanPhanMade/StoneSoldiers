// ©Van Phan

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ETerrainType : uint8
{
	Clear,
	Forest
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
