// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.generated.h"

UENUM()
enum EDamageTypes : uint8
{
	Slashing,
	Piercing,
	Crushing,
	Magic
};


USTRUCT(BlueprintType)
struct FWeaponDataStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EDamageTypes> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Damage;

	FWeaponDataStruct():
		DamageType(TEnumAsByte<EDamageTypes>(Slashing)),
		Range(0),
		Damage(0) {}
};


/**
 * 
 */
class STONESOLDIERS_API WeaponData
{
public:
	WeaponData();
	~WeaponData();
};
