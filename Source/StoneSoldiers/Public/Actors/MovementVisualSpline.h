// ©Van Phan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementVisualSpline.generated.h"

UCLASS()
class STONESOLDIERS_API AMovementVisualSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovementVisualSpline();

	void GenerateSpline(FVector A, FVector B);
	void UpdateSplineMeshes(FVector A, FVector B);
	void SetVisibilityForSpline(bool Visibility);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* SplineMesh;

	UPROPERTY(EditAnywhere, Category = "Spline")
	float SplineHeight = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Spline")
	float SplineScale = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	uint8 NumPoints = 10; 

	TArray<class UStaticMeshComponent*> CachedMeshes;

};
