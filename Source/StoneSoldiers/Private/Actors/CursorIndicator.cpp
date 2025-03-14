// ©Van Phan


#include "Actors/CursorIndicator.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

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

bool ACursorIndicator::DisplayCharacterInfo(bool bShow)
{
	CharacterInfoWidget->SetVisibility(bShow);
	CharacterInfoWidget->SetWorldLocation(GetActorLocation() + FVector(0, 0, 300.0f));
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

