// ©Van Phan

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType) 
enum EStoneSoldierDifficulty : int8
{
  Easy     			    UMETA(DisplayName = "Easy"),
  Medium     		    UMETA(DisplayName = "Medium"),
  Hard  			      UMETA(DisplayName = "Hard"),
  DifficultyNONE  	UMETA(DisplayName = "DifficultyNONE"),
};

UENUM(BlueprintType) 
enum ETileType : int8
{
  Square     			    UMETA(DisplayName = "Square"),
  Triangle     		    UMETA(DisplayName = "Triangle"),
  Hexagon  			      UMETA(DisplayName = "Hexagon"),
  TileTypeNONE  	    UMETA(DisplayName = "TileTypeNONE"),
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
