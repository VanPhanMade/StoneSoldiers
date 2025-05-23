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

	/**
	 * @brief Displays the in game UI over the cursor when hovering over a unit
	 * @param bShow sets the visibility to this value
	 * @param bCharactersFight whether to use the UI that displays a unit vs another unit
	 * @param attacker the instigator of an attack, if there is one, cached in the game state
	 * @param defender the tile we are instigating the action towards ( the unit being attacked or targeted )
	 * @return returns false if any errors with loading the UI, or retrieving data occur
	 */
	virtual bool DisplayCharacterInfo(bool bShow, bool bCharactersFight, const class ABaseUnit* attacker, const class ABaseUnit* defender);
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
