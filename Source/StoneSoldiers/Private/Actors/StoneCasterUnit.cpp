/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Actors/StoneCasterUnit.h"
#include "Actors/GolemUnit.h"

void AStoneCasterUnit::AddControlledGolem(AGolemUnit* Golem)
{
	ControlledGolems.Add(Golem);
}
