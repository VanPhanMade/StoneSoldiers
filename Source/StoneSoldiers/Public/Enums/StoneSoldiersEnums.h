// ©Van Phan

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType) 
enum EStoneSoldierDifficulty : int8
{
  Easy     			UMETA(DisplayName = "Easy"),
  Medium     		UMETA(DisplayName = "Medium"),
  Hard  			UMETA(DisplayName = "Hard"),
  DifficultyNONE  	UMETA(DisplayName = "DifficultyNONE"),
};
/**
 * 
 */
class STONESOLDIERS_API StoneSoldiersEnums
{
public:
	StoneSoldiersEnums();
	~StoneSoldiersEnums();
};
