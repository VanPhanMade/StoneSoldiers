#include "Pawns/StoneSoldiersPlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AStoneSoldiersPlayerPawn::AStoneSoldiersPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent) RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(SpringArm);
}

void AStoneSoldiersPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	
}

void AStoneSoldiersPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoneSoldiersPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &ThisClass::PrimaryActionCall);
		EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &ThisClass::SecondaryActionCall);
		EnhancedInputComponent->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &ThisClass::ForwardActionCall);
		EnhancedInputComponent->BindAction(LeftAction, ETriggerEvent::Triggered, this, &ThisClass::LeftActionCall);
		EnhancedInputComponent->BindAction(RightAction, ETriggerEvent::Triggered, this, &ThisClass::RightActionCall);
		EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Triggered, this, &ThisClass::BackActionCall);
		EnhancedInputComponent->BindAction(ScreenMovementAction, ETriggerEvent::Ongoing, this, &ThisClass::ScreenMovementActionCall);
		EnhancedInputComponent->BindAction(OpenMenuAction, ETriggerEvent::Triggered, this, &ThisClass::OpenMenuActionCall);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::ZoomActionCall);
	}

}

void AStoneSoldiersPlayerPawn::PrimaryActionCall()
{
	StoneSoldiersHelperFunctions::LogEngineMessage("Primary action clicked");
}

void AStoneSoldiersPlayerPawn::SecondaryActionCall()
{

}

void AStoneSoldiersPlayerPawn::ForwardActionCall()
{

}

void AStoneSoldiersPlayerPawn::LeftActionCall() 
{

}

void AStoneSoldiersPlayerPawn::RightActionCall()
{

}

void AStoneSoldiersPlayerPawn::BackActionCall()
{

}

void AStoneSoldiersPlayerPawn::ScreenMovementActionCall(const FInputActionValue &Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if (InputVector.Length() != 0)
    {
        // Process the mouse movement here
        StoneSoldiersHelperFunctions::LogEngineMessage("Screen movement action fired");
        
        // For example, you can use the InputVector to control the camera or perform other actions
        // Add your camera movement logic here, e.g., adjust camera rotation or position based on InputVector
    }
}

void AStoneSoldiersPlayerPawn::OpenMenuActionCall()
{

}

void AStoneSoldiersPlayerPawn::ZoomActionCall(const FInputActionValue& Value)
{

}
