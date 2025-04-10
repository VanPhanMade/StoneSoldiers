// ©Van Phan


#include "Widgets/WidgetCursorAndItemDisplay.h"

#include "Components/WidgetSwitcher.h"

bool UWidgetCursorAndItemDisplay::DisplayOneUnitData()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		return true;
	}

	return false;
}

bool UWidgetCursorAndItemDisplay::Initialize()
{
	return Super::Initialize();
}

bool UWidgetCursorAndItemDisplay::DisplayTwoUnitFightingData()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
		return true;
	}
	return false;
}
