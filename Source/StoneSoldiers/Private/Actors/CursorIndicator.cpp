/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Actors/CursorIndicator.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "Widgets/WidgetCursorAndItemDisplay.h"

ACursorIndicator::ACursorIndicator()
{
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent) RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	CharacterInfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CharacterInfo"));
	CharacterInfoWidget->SetupAttachment(RootComponent);

	CursorIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CursorMesh"));
	CursorIndicatorMesh->SetupAttachment(RootComponent);

	CursorIndicatorRotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
	CursorIndicatorRotatingMovement->RotationRate = FRotator(0.f, 90.f, 0.f);
	
	CharacterInfoWidget->SetWidgetSpace(EWidgetSpace::Screen);
	CharacterInfoWidget->SetDrawSize(FVector2D(750, 250));
	CharacterInfoWidget->SetVisibility(false);
}

bool ACursorIndicator::DisplayCharacterInfo(bool bShow, bool bCharactersFight, const class ABaseUnit* attacker, const class ABaseUnit* defender)
{
	CharacterInfoWidget->SetVisibility(bShow);
	CharacterInfoWidget->SetWorldLocation(GetActorLocation() + FVector(0, 0, 300.0f));
	UUserWidget* Widget = CharacterInfoWidget->GetUserWidgetObject();
	if (UWidgetCursorAndItemDisplay* CharacterInfoUI = Cast<UWidgetCursorAndItemDisplay>(Widget))
	{
		if (bCharactersFight)
		{
			CharacterInfoUI->DisplayTwoUnitFightingData(attacker, defender);
		}
		else
		{
			CharacterInfoUI->DisplayOneUnitData(defender);
		}
	}
	else
	{
		StoneSoldiersHelperFunctions::LogEngineMessage("Can't cast widget to Character Info Widget | ACursorIndicator | DisplayCharacterInfo");
	}
	return CharacterInfoWidget != nullptr;
}

bool ACursorIndicator::DisplayCursorMesh(bool bShow)
{
	CursorIndicatorMesh->SetVisibility(bShow);
	return CursorIndicatorMesh != nullptr;
}

void ACursorIndicator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACursorIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

