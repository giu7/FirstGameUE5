// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"

#include "Components/BoxComponent.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ROOT"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AShipController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + Speed * CurrentVelocity * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent -> BindAxis("MoveX", this, &AShipController::MoveXAxis);
	InputComponent -> BindAxis("MoveY", this, &AShipController::MoveYAxis);
}

void AShipController::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 100.0f;
}

void AShipController::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}
