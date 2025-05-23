/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/

#include "Pawns/SS_PlayerPawn_Singleplayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/ClickableInterface.h"
#include "Interfaces/HoverableInterface.h"
#include "GameFramework/PlayerController.h"
#include "Actors/GolemUnit.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "PlayerControllers/StoneSoldiersPlayerController.h"
#include "PlayerStates/StoneSoldierPlayerState.h"

ASS_PlayerPawn_Singleplayer::ASS_PlayerPawn_Singleplayer()
{
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent) RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraComponent->SetupAttachment(SpringArm);
}

void ASS_PlayerPawn_Singleplayer::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		FInputModeGameAndUI InputMode;
        InputMode.SetHideCursorDuringCapture(false);
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
        InputMode.SetWidgetToFocus(nullptr); // Allow for input to pass through
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = true; // Show the mouse cursor

		CurrentZoomTarget = SpringArm->TargetArmLength;
	}

	if (AStoneSoldiersPlayerController* PC = Cast<AStoneSoldiersPlayerController>(GetController()))
	{
		for (auto WeakUnit : ControlledUnits)
		{
			if (WeakUnit.IsValid())
			{
				PC->AddControlledUnit(WeakUnit.Get());
				if (!WeakUnit.Get()->OnUnitDeathDelegate.IsAlreadyBound(this, &ThisClass::DestroyUnit))
				{
					WeakUnit.Get()->OnUnitDeathDelegate.AddDynamic(this, &ThisClass::DestroyUnit);
				}
			}
		}
		for (auto units : PC->GetControlledUnits())
		{
			units->OnTurnFinishedDelegate.AddDynamic(this, &ThisClass::EndUnitTurn);
		}
	}
	
	if (UWorld* World = GetWorld())
	{
		if (AStoneSoldiersGameState* GS = World->GetGameState<AStoneSoldiersGameState>())
		{
			if (GS->PlayersInGame.Num() == GS->NumPlayers )
			{
				GS->NextPlayerTurn();
			}
		}
	}
}

void ASS_PlayerPawn_Singleplayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float TargetArmLength = FMath::Clamp(CurrentZoomTarget, 500.0f, 900.0f);
    SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetArmLength, DeltaTime, 5);
}

void ASS_PlayerPawn_Singleplayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

		EnhancedInputComponent->BindAction(ScreenMovementAction, ETriggerEvent::Triggered, this, &ThisClass::ScreenMovementActionCall);
		InputComponent->BindAxis("MouseX", this, &ThisClass::MouseXMovement);
    	InputComponent->BindAxis("MouseY", this, &ThisClass::MouseYMovement);


		EnhancedInputComponent->BindAction(OpenMenuAction, ETriggerEvent::Triggered, this, &ThisClass::OpenMenuActionCall);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::ZoomActionCall);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::MoveActionCall);
	}
}

TScriptInterface<IClickableInterface> ASS_PlayerPawn_Singleplayer::GetClickedActor()
{
	FHitResult HitResult;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && PlayerController->IsLocalController())
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	}

	if (HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();
		return TScriptInterface<IClickableInterface>(HitActor);
	}

	return nullptr;
}

void ASS_PlayerPawn_Singleplayer::PrimaryActionCall()
{
	if (const TScriptInterface<IClickableInterface> Clickable = GetClickedActor())
	{
		Clickable->OnLeftClick(Controller);
	}

}

void ASS_PlayerPawn_Singleplayer::SecondaryActionCall()
{
	if (const TScriptInterface<IClickableInterface> Clickable = GetClickedActor())
	{
		Clickable->OnRightClick(Controller);
	}
	else
	{
		AStoneSoldierPlayerState* PS = GetController()->GetPlayerState<AStoneSoldierPlayerState>();
		PS->PopAndGoBackAState(); 
	}
}

void ASS_PlayerPawn_Singleplayer::ForwardActionCall()
{
	
}

void ASS_PlayerPawn_Singleplayer::LeftActionCall() 
{
	
}

void ASS_PlayerPawn_Singleplayer::RightActionCall()
{
	
}

void ASS_PlayerPawn_Singleplayer::BackActionCall()
{
	
}

void ASS_PlayerPawn_Singleplayer::ScreenMovementActionCall(const FInputActionValue &Value)
{
	// FVector2D InputVector = Value.Get<FVector2D>();
}

void ASS_PlayerPawn_Singleplayer::OpenMenuActionCall()
{
	StoneSoldiersHelperFunctions::LogEngineMessage("Open menu action clicked");
}

void ASS_PlayerPawn_Singleplayer::ZoomActionCall(const FInputActionValue& Value)
{
	float ScrollValue = Value.Get<float>();
    if (ScrollValue != 0)
    {
        // Calculate a new arm length based on scroll input
        CurrentZoomTarget = SpringArm->TargetArmLength + ScrollValue * -100.0f; // Adjust multiplier as needed

        // Clamp the target length between the min and max
        CurrentZoomTarget = FMath::Clamp(CurrentZoomTarget, 400.0f, 1000.0f);

    }
}

void ASS_PlayerPawn_Singleplayer::MoveActionCall(const FInputActionValue &Value)
{
    FVector2D InputVector = Value.Get<FVector2D>();
	FVector Direction = (GetActorForwardVector() * InputVector.Y * 5.0f) + (GetActorRightVector() * InputVector.X * 5.0f);
	SetActorLocation(GetActorLocation() + Direction);
}

void ASS_PlayerPawn_Singleplayer::MouseXMovement(float Value)
{
	FHitResult HitResult;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && PlayerController->IsLocalController())
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	}

	// Get the currently hovered object, if valid
	IHoverableInterface* CurrentObject = Cast<IHoverableInterface>(CurrentHoveredObject.Get());

	if (HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();
		IHoverableInterface* HoverableActor = Cast<IHoverableInterface>(HitActor);
		// If we hit a valid hoverable actor, and it's different from the currently hovered object
		if (HoverableActor && (HoverableActor != CurrentObject))
		{
			if (CurrentObject)
			{
				CurrentObject->OnHoverEnd(Controller);
			}

			HoverableActor->OnHoverBegin(Controller);
			CurrentHoveredObject = HitActor;
		}
		else if (!HoverableActor && CurrentObject) // Hit a non-hoverable actor, end hover if necessary
		{
			CurrentObject->OnHoverEnd(Controller);
			CurrentHoveredObject.Reset();
		}
	}
	else if (CurrentHoveredObject.IsValid()) // No hit result at all, end hover if necessary
	{
		CurrentObject->OnHoverEnd(Controller);
		CurrentHoveredObject.Reset();
	}
}

void ASS_PlayerPawn_Singleplayer::MouseYMovement(float Value)
{

}

void ASS_PlayerPawn_Singleplayer::SpawnUnits()
{
    Super::SpawnUnits();
}

void ASS_PlayerPawn_Singleplayer::PlaceUnits()
{
    Super::PlaceUnits();
}

void ASS_PlayerPawn_Singleplayer::DestroyUnit(class ABaseUnit* Unit)
{
	Super::DestroyUnit(Unit);
	if (AStoneSoldiersPlayerController* PC = Cast<AStoneSoldiersPlayerController>(GetController()))
	{
		PC->RemoveControlledUnit(Unit);
	}
}

void ASS_PlayerPawn_Singleplayer::StartPlayerTurn()
{
	Super::StartPlayerTurn();
}

void ASS_PlayerPawn_Singleplayer::EndUnitTurn(ABaseUnit* Unit)
{
    UWorld* World = GetWorld();
    AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();
	
    int32 index = UnitsToActivate.Find(Unit);
    if (index != -1)
    {
        UnitsToActivate.RemoveAt(index);
        GameState->ActiveUnit = nullptr;
        if (UnitsToActivate.Num() == 0)
        {
            
            GameState->NextPlayerTurn();
        }
    }
}
