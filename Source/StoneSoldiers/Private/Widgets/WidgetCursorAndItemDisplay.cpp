/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Widgets/WidgetCursorAndItemDisplay.h"

#include "Actors/BaseUnit.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

bool UWidgetCursorAndItemDisplay::DisplayOneUnitData(const ABaseUnit* ActiveUnit)
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		if (ActiveUnitCurrentHealth && ActiveUnitMaxHealth && ActiveUnit)
		{
			ActiveUnitCurrentHealth->SetText(FText::AsNumber(ActiveUnit->GetCurrentHealth())); 
			ActiveUnitMaxHealth->SetText(FText::AsNumber(ActiveUnit->GetUnitData().UnitCoreData.Health)); 
		}
		return ActiveUnit != nullptr;
	}

	return false;
}

bool UWidgetCursorAndItemDisplay::Initialize()
{
	return Super::Initialize();
}

bool UWidgetCursorAndItemDisplay::DisplayTwoUnitFightingData(const ABaseUnit* Attacker, const ABaseUnit* Defender)
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
		return Attacker != nullptr && Defender != nullptr;
	}
	return false;
}
