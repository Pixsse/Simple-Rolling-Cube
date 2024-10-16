// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RollingCubeComponent.generated.h"

UENUM(BlueprintType)
enum class ERollDirection : uint8
{
	Forward		UMETA(DisplayName	= "Forward"),
	Backward	UMETA(DisplayName	= "Backward"),
	Right		UMETA(DisplayName	= "Right"),
	Left		UMETA(DisplayName	= "Left")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLEROLLINGCUBE_API URollingCubeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URollingCubeComponent();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Debug")
	bool bDebug = false;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Rolling Cube")
	float CubeSize = 100.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Rolling Cube")
	float RollAngle = 90.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rolling Cube")
	float RollSpeed = 50.f;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Rolling Cube")
	TEnumAsByte<ECollisionChannel> CollisionType = ECC_Visibility;

public:
	UFUNCTION(BlueprintCallable, Category = "Rolling Cube")
	void UpdateCubeMovement(ERollDirection Direction);

private :
	bool bIsMoving;
	float CurrentAngle;
	FVector LastActorLocation;
	FVector FinalActorLocation;
	ERollDirection CurrentDirection;

private:
	void UpdateRollingCube(float DeltaTime);
	bool HasCollisionAbove(ERollDirection Direction);
	bool HasCollisionInFront(ERollDirection Direction);
	bool HasCollisionBelow(ERollDirection Direction);
	bool BoxTrace(FVector Start, FVector End);
	FVector GetInputVectorDirection(ERollDirection Direction);
};
