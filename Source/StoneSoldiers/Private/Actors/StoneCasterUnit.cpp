// ©Van Phan


#include "Actors/StoneCasterUnit.h"
#include "Actors/GolemUnit.h"

void AStoneCasterUnit::AddControlledGolem(AGolemUnit* Golem)
{
	ControlledGolems.Add(Golem);
}
