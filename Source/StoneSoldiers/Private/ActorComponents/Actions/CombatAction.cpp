/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "ActorComponents/Actions/CombatAction.h"
#include "Structs/WeaponData.h"
#include "Actors/UnitTile.h"

void UCombatAction::UseAction(ABaseUnit* Target)
{
	int Damage = OwningUnit->GetCurrentWeaponDamage() - Target->GetCurrentDefenses()[OwningUnit->CurrentWeapon.DamageType];
	Target->ResolveDamage(Damage);
}
