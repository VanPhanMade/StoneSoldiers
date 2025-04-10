// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CursorIndicator.generated.h"

UCLASS()
class STONESOLDIERS_API ACursorIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	ACursorIndicator();

	virtual bool DisplayCharacterInfo(bool bShow, bool bCharactersFight);
	virtual bool DisplayCursorMesh(bool bShow);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* CharacterInfoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CursorIndicatorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent* CursorIndicatorRotatingMovement;
	
	

};
