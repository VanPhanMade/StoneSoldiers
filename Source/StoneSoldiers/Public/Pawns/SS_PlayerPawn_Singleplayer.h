// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SS_PlayerPawn_Singleplayer.generated.h"

UCLASS()
class STONESOLDIERS_API ASS_PlayerPawn_Singleplayer : public APawn
{
	GENERATED_BODY()

public:
	ASS_PlayerPawn_Singleplayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	

};
