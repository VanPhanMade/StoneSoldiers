// ©Van Phan

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EUnitAIStance : uint8
{
	Standard,
	Defensive,
	Aggressive,
	Static,
	Inactive
};



/**
 * 
 */
class STONESOLDIERS_API AIEnums
{
public:
	AIEnums();
	~AIEnums();
};
