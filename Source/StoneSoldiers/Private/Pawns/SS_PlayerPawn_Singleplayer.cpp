// ©Van Phan


#include "Pawns/SS_PlayerPawn_Singleplayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Utilities/StoneSoldiersHelperFunctions.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/ClickableInterface.h"
#include "Interfaces/HoverableInterface.h"
#include "GameFramework/PlayerController.h"
#include "Actors/StoneCasterUnit.h"
#include "Actors/GolemUnit.h"
#include "Actors/MovementVisualSpline.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "GameModes/SS_Gamemode_Singleplayer.h"
#include "PlayerControllers/SS_PlayerController_Singleplayer.h"
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

    //Temp Unit Spawning
    SpawnUnits();
    PlaceUnits();

    UWorld* World = GetWorld();
    World->GetGameState<AStoneSoldiersGameState>()->RegisterPlayer(ID, this);
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


IClickableInterface* ASS_PlayerPawn_Singleplayer::GetClickedActor()
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
        return Cast<IClickableInterface>(HitActor);
    }

    return nullptr;
}



void ASS_PlayerPawn_Singleplayer::PrimaryActionCall()
{
    IClickableInterface* ClickedActor = GetClickedActor();

    if (ClickedActor)
    {
        if (ClickedActor != CurrentClicked)
        {
            // Change focus to new actor
            ClickedActor->OnLeftClick();
            CurrentClicked = ClickedActor;

        	// Update UI based off state
        	AStoneSoldierPlayerState* PS = GetController()->GetPlayerState<AStoneSoldierPlayerState>();
        	ASS_PlayerController_Singleplayer* PC = Cast<ASS_PlayerController_Singleplayer>(GetController());
			
        	if (PS->GetCurrenState()->StateName == "Choosing Unit Action")
        	{
        		PC->SwapToGameplayInteractionOptionsUI();
        	}
        	else if (PS->GetCurrenState()->StateName == "My Turn" || PS->GetCurrenState()->StateName == "Not My Turn")
        	{
        		PC->SwapToDefaultInGameUI();
        		UWorld* World = GetWorld();
        		if (AStoneSoldiersGameState* GS = World->GetGameState<AStoneSoldiersGameState>())
        		{
        			if (PS->GetCurrenState()->StateName != "Moving Unit") GS->GetMovementSpline()->SetVisibilityForSpline(false);
        		}
        	}
        	
        }
        else if (CurrentClicked)
        {
            // Call on the current actor if it's already focused
            CurrentClicked->OnLeftClick();
        }

    	
    }
}

void ASS_PlayerPawn_Singleplayer::SecondaryActionCall()
{
	IClickableInterface* ClickedActor = GetClickedActor();
	
	if (CurrentClicked)
	{
		CurrentClicked->OnRightClick();
	}

	AStoneSoldierPlayerState* PS = GetController()->GetPlayerState<AStoneSoldierPlayerState>();
	ASS_PlayerController_Singleplayer* PC = Cast<ASS_PlayerController_Singleplayer>(GetController());
	PS->PopAndGoBackAState(); 
	if (PS->GetCurrenState()->StateName == "My Turn")
	{
		PC->SwapToDefaultInGameUI();
	}
	StoneSoldiersHelperFunctions::LogEngineMessage("Current State: " + PS->GetCurrenState()->StateName + " ASS_PlayerPawn_SinglePlayer | SecondaryActionCall");

	
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

    // Check if we hit something and if it's a hoverable actor
    if (HitResult.bBlockingHit)
    {
        AActor* HitActor = HitResult.GetActor();
        IHoverableInterface* HoverableActor = Cast<IHoverableInterface>(HitActor);

        // If we hit a valid hoverable actor, and it’s different from the current hovered object
        if (HoverableActor && HoverableActor != CurrentHoveredObject)
        {
            // End hover on the previously hovered object, if any
            if (CurrentHoveredObject)
            {
                CurrentHoveredObject->OnHoverEnd();
            }

            // Start hover on the new hoverable object
            HoverableActor->OnHoverBegin();
            CurrentHoveredObject = HoverableActor;
        }
        else if (!HoverableActor && CurrentHoveredObject) // Hit a non-hoverable actor, end hover if necessary
        {
            CurrentHoveredObject->OnHoverEnd();
            CurrentHoveredObject = nullptr;
        }
    }
    else if (CurrentHoveredObject) // No hit result at all, end hover if necessary
    {
        CurrentHoveredObject->OnHoverEnd();
        CurrentHoveredObject = nullptr;
    }

    // Optional debug visualization for the hit location
    // if (HitResult.bBlockingHit)
    // {
    //     DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.0f, 12, FColor::Green, false, 2.0f);
    // }
}


void ASS_PlayerPawn_Singleplayer::MouseYMovement(float Value)
{
	// FString Message = FString::Printf(TEXT("Screen movement action fired: Mouse& Value = %f"), Value);
	// StoneSoldiersHelperFunctions::LogEngineMessage(*Message);

}


void ASS_PlayerPawn_Singleplayer::SpawnUnits()
{
    UWorld* World = GetWorld();
    ABaseUnit* Unit = nullptr;
    AStoneCasterUnit* PreviousStoneCaster = nullptr;

    for (int i = 0; i < SelectedUnitData.Num(); i++)
    {
        FTransform Transform = FTransform();
        FVector Location = GetActorLocation() + FVector(0.0, i * 150, 0.0);
        Transform.SetLocation(Location);

        Unit = Cast<ASS_Gamemode_Singleplayer>(World->GetAuthGameMode())->CreateUnit(SelectedUnitData[i]);
        Unit->Init(SelectedUnitData[i], ID);

        // If StoneCaster
        if (Unit->GetUnitData().Type == StoneCaster)
        {
            PreviousStoneCaster = Cast<AStoneCasterUnit>(Unit);
        }

        // If Golem
        if (Unit->GetUnitData().Type == Golem)
        {
            PreviousStoneCaster->AddControlledGolem(Cast<AGolemUnit>(Unit));
            Cast<AGolemUnit>(Unit)->SetControllingCaster(PreviousStoneCaster);
        }

        if (Unit != nullptr)
        {
            ControlledUnits.Add(Unit);
            //UnitsToActivate.Add(Unit);
            //Unit->OnTurnFinishedDelegate.AddDynamic(this, &AStoneSoldiersGameState::UnitTurnFinished);
            Unit->OnTurnFinishedDelegate.AddDynamic(this, &ASS_PlayerPawn_Singleplayer::EndUnitTurn);
        }
        Unit = nullptr;
    }

    // TEMP ENEMY SPAWNING
    //TestEnemyUnit = Cast<ASS_Gamemode_Singleplayer>(World->GetAuthGameMode())->CreateUnit(SelectedUnitData[0]);
    //TestEnemyUnit->Init(SelectedUnitData[0], UPlayerID::Player2);

    //StoneSoldiersHelperFunctions::LogEngineMessage(FString(FString::FromInt(ControlledUnits.Num())));
    // StoneSoldiersHelperFunctions::LogEngineMessage(FString(FString::FromInt(PreviousStoneCaster->GetControlledNum())));
}

void ASS_PlayerPawn_Singleplayer::PlaceUnits()
{
    UWorld* World = GetWorld();
    AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();

    for (int i = 0; i < ControlledUnits.Num(); i++)
    {
        GameState->PlaceUnit(ControlledUnits[i], FVector(i, 0, -i));
    }

    GameState->PlayerUnits.Add(ID, ControlledUnits);
    GameState->TeamUnits.Add(TeamID, ControlledUnits);
}

void ASS_PlayerPawn_Singleplayer::StartPlayerTurn()
{
	UWorld* World = GetWorld();
	AStoneSoldiersGameState* GameState = World->GetGameState<AStoneSoldiersGameState>();
    UnitsToActivate = GameState->PlayerUnits[ID];

    for (ABaseUnit* UnitToReset : UnitsToActivate)
    {
    	if (UnitToReset) UnitToReset->State = EUnitState::Ready;
    	else { StoneSoldiersHelperFunctions::LogEngineMessage(FString("Null unit in Units To Active | SinglePlayerPawn | Start Player Turn")); }
    }
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
			
            /*
            UnitsToActivate = ControlledUnits;

            for (ABaseUnit* UnitToReset : UnitsToActivate)
            {
                UnitToReset->State = UUnitState::Ready;
            }
            */
        }
    }
}
