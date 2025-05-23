// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameStates/StoneSoldiersGameState.h"
#include "GameFramework/Pawn.h"
#include "Structs/UnitData.h"
#include "Pawns/PlayerPawn.h"
#include "SS_PlayerPawn_Singleplayer.generated.h"

UENUM()
enum PlayerTurnState : uint8
{
	Inactive,
	MovingUnit,
	ActivatingUnit
};

UCLASS()
class STONESOLDIERS_API ASS_PlayerPawn_Singleplayer : public APlayerPawn
{
	GENERATED_BODY()

public:
	ASS_PlayerPawn_Singleplayer();
	virtual void StartPlayerTurn() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// Left and right click
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PrimaryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SecondaryAction;

	// WASD for movement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Axis input for tracking mouse movement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ScreenMovementAction;

	// Toggles in-game main menu options
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* OpenMenuAction;

	// Scroll wheel
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ZoomAction;

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// Input callbacks
	void PrimaryActionCall();
	void SecondaryActionCall();
	void ForwardActionCall();
	void LeftActionCall();
	void RightActionCall();
	void BackActionCall();
	void ScreenMovementActionCall(const struct FInputActionValue& Value);
	void OpenMenuActionCall();
	void ZoomActionCall(const struct FInputActionValue& Value);
	void MoveActionCall(const struct FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void MouseXMovement(float Value);
	UFUNCTION(BlueprintCallable)
    void MouseYMovement(float Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurrentZoomTarget = 700.0f;

	UFUNCTION()
    TScriptInterface<IClickableInterface> GetClickedActor();

	TWeakObjectPtr<AActor> CurrentHoveredObject;

	// Unit Management
	virtual void SpawnUnits() override;
	virtual void PlaceUnits() override;

	UFUNCTION()
	virtual void DestroyUnit(class ABaseUnit* Unit) override;

	UFUNCTION()
	void EndUnitTurn(class ABaseUnit* Unit);
};
