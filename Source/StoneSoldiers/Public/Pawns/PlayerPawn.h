// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class STONESOLDIERS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerPawn();

	// Called to have the AI Run its turn
	virtual void StartPlayerTurn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:	
	

};
