// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingCubePawn.h"

// Sets default values
ARollingCubePawn::ARollingCubePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

	RollingCubeComponent = CreateDefaultSubobject<URollingCubeComponent>(TEXT("RollingCubeComponent"));
	
}

// Called when the game starts or when spawned
void ARollingCubePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARollingCubePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARollingCubePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

