// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollingCubeComponent.h"
#include "RollingCubePawn.generated.h"

UCLASS()
class SIMPLEROLLINGCUBE_API ARollingCubePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollingCubePawn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URollingCubeComponent* RollingCubeComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* CubeMesh;
};
