// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingCubeComponent.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
URollingCubeComponent::URollingCubeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URollingCubeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void URollingCubeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsMoving) return;

	UpdateRollingCube(DeltaTime);
}

void URollingCubeComponent::UpdateCubeMovement(ERollDirection Direction)
{
	if (bIsMoving) return;
	if (HasCollisionAbove(Direction)) return;
	if (HasCollisionInFront(Direction)) return;
	if (!HasCollisionBelow(Direction)) return;

	FVector DirectionVector = GetInputVectorDirection(Direction);

	bIsMoving = true;
	CurrentAngle = 0.f;
	CurrentDirection = Direction;
	LastActorLocation = GetOwner()->GetActorLocation();
	FinalActorLocation = LastActorLocation + DirectionVector * CubeSize;
}

void URollingCubeComponent::UpdateRollingCube(float DeltaTime)
{
	float AngleToRotate = RollSpeed * DeltaTime;
	CurrentAngle += AngleToRotate;

	if (CurrentAngle >= RollAngle)
	{
		AngleToRotate -= (CurrentAngle - RollAngle);
		CurrentAngle = RollAngle;
		bIsMoving = false;
	}

	FVector ActorLocation = GetOwner()->GetActorLocation();
	FRotator ActorRotation = GetOwner()->GetActorRotation();

	FVector HalfPoint = (LastActorLocation + FinalActorLocation) / 2.f;
	HalfPoint.Z += CubeSize / 2.f;

	FVector NewActorLocation = FMath::Lerp(
		FMath::Lerp(LastActorLocation, HalfPoint, CurrentAngle / RollAngle),
		FMath::Lerp(HalfPoint, FinalActorLocation, CurrentAngle / RollAngle),
		CurrentAngle / RollAngle
	);

	FVector InputDirection = GetInputVectorDirection(CurrentDirection);
	FVector RotationAxis = FVector::CrossProduct(FVector::UpVector, InputDirection).GetSafeNormal();

	FQuat DeltaRotationQuat = FQuat(RotationAxis, FMath::DegreesToRadians(AngleToRotate));
	FQuat NewRotationQuat = DeltaRotationQuat * GetOwner()->GetActorQuat();

	GetOwner()->SetActorLocationAndRotation(NewActorLocation, NewRotationQuat.Rotator());

	if (!bIsMoving) LastActorLocation = GetOwner()->GetActorLocation();
}

bool URollingCubeComponent::HasCollisionAbove(ERollDirection Direction)
{
	FVector DirectionVector = GetInputVectorDirection(Direction);

	FVector Start = GetOwner()->GetActorLocation() + FVector(0.f, 0.f, CubeSize);
	FVector End = Start + DirectionVector * CubeSize;

	return BoxTrace(Start, End);
}

bool URollingCubeComponent::HasCollisionInFront(ERollDirection Direction)
{
	FVector DirectionVector = GetInputVectorDirection(Direction);

	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + DirectionVector * CubeSize;

	return BoxTrace(Start, End);
}

bool URollingCubeComponent::HasCollisionBelow(ERollDirection Direction)
{
	FVector DirectionVector = GetInputVectorDirection(Direction);

	FVector Start = GetOwner()->GetActorLocation() + -FVector(0.f, 0.f, CubeSize) + DirectionVector * CubeSize;
	FVector End = Start;

	return BoxTrace(Start, End);
}

bool URollingCubeComponent::BoxTrace(FVector Start, FVector End)
{
	FVector BoxExtent = FVector(CubeSize / 2.5f);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, CollisionType, FCollisionShape::MakeBox(BoxExtent), CollisionParams);

	if (bDebug)
	{
		DrawDebugBox(GetWorld(), Start, BoxExtent, FQuat::Identity, FColor::Magenta, false, 2, 0, 1);
		DrawDebugBox(GetWorld(), End, BoxExtent, FQuat::Identity, FColor::Red, false, 2, 0, 1);
	}

	return bHit;
}

FVector URollingCubeComponent::GetInputVectorDirection(ERollDirection Direction)
{
	switch (Direction)
	{
	case ERollDirection::Forward:
		return FVector::ForwardVector;
	case ERollDirection::Backward:
		return FVector::BackwardVector;
	case ERollDirection::Right:
		return FVector::RightVector;
	case ERollDirection::Left:
		return FVector::LeftVector;
	default:
		return FVector::ZeroVector;
	}
}



