/*
© 2025 Crossing Worlds Entertainment, LLC. All Rights Reserved.
*/


#include "Actors/MovementVisualSpline.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

AMovementVisualSpline::AMovementVisualSpline()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AMovementVisualSpline::GenerateSpline(FVector A, FVector B)
{
	for (UStaticMeshComponent* MeshComp : CachedMeshes)
	{
		if (MeshComp)
		{
			MeshComp->DestroyComponent();
			MeshComp = nullptr;
		}
	}
	CachedMeshes.Empty();

	// Generate new mesh components along the curve
	for (int i = 0; i < NumPoints; ++i)
	{
		float t = static_cast<float>(i) / (NumPoints - 1); // Normalized range [0,1]

		// Compute position using linear interpolation
		FVector Pos = FMath::Lerp(A, B, t);
        
		// Apply sine wave elevation
		float Amplitude = SplineHeight * SplineScale; 
		Pos.Z += Amplitude * FMath::Sin(t * PI);

		// Create and configure the mesh component
		UStaticMeshComponent* MeshComp = NewObject<UStaticMeshComponent>(this);
		MeshComp->SetStaticMesh(SplineMesh);
		MeshComp->SetMobility(EComponentMobility::Movable);
		MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		MeshComp->RegisterComponent();
		MeshComp->SetWorldLocation(Pos);
		MeshComp->SetWorldScale3D(FVector(SplineScale)); 
		AddInstanceComponent(MeshComp);

		// Cache the component for visibility toggling
		CachedMeshes.Add(MeshComp);

		UE_LOG(LogTemp, Log, TEXT("Generated %d spline mesh components."), CachedMeshes.Num());
	}
}

void AMovementVisualSpline::UpdateSplineMeshes(FVector A, FVector B)
{
	// Ensure we have at least one mesh
	if (CachedMeshes.Num() == 0) return;

	// Determine segment count based on mesh array size
	int NumSegments = CachedMeshes.Num();
	float SegmentLength = 1.0f / NumSegments; // Normalized [0,1] step

	// Calculate amplitude based on A to B distance
	float Amplitude = SplineHeight * SplineScale;

	for (int i = 0; i < NumSegments; ++i)
	{
		float t0 = i * SegmentLength;
		float t1 = (i + 1) * SegmentLength;

		// Compute positions
		FVector StartPos = FMath::Lerp(A, B, t0);
		FVector EndPos = FMath::Lerp(A, B, t1);

		// Apply sine wave height
		StartPos.Z += Amplitude * FMath::Sin(t0 * PI);
		EndPos.Z += Amplitude * FMath::Sin(t1 * PI);

		// Compute forward direction
		FVector ForwardDir = (EndPos - StartPos).GetSafeNormal();

		// Compute slope for pitch adjustment
		float dZ_dt = Amplitude * PI * FMath::Cos(t0 * PI);
		float PitchAngle = FMath::RadiansToDegrees(FMath::Atan(dZ_dt / FVector::Distance(StartPos, EndPos)));

		// Compute rotation
		FRotator MeshRotation = FRotationMatrix::MakeFromXZ(ForwardDir, FVector(0, 0, 1)).Rotator();
		MeshRotation.Pitch = PitchAngle;

		// Update mesh transform
		if (CachedMeshes[i])
		{
			CachedMeshes[i]->SetWorldLocation(StartPos);
			CachedMeshes[i]->SetWorldRotation(MeshRotation);
			CachedMeshes[i]->SetWorldScale3D(FVector(SplineScale));
		}
	}
}

void AMovementVisualSpline::SetVisibilityForSpline(bool Visibility)
{
	for (UStaticMeshComponent* MeshComp : CachedMeshes)
	{
		if (MeshComp)
		{
			MeshComp->SetVisibility(Visibility);
			MeshComp->SetHiddenInGame(!Visibility);
		}
	}
}

void AMovementVisualSpline::BeginPlay()
{
	Super::BeginPlay();

	FVector A = GetActorLocation();
	FVector B = A + FVector(500, 0, 0);

	GenerateSpline(A, B);
	SetVisibilityForSpline(false);
}

void AMovementVisualSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

