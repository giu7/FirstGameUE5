// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipController.h"

#include "EnemyController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShipController::AShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ROOT"));
	CollisionBox -> SetGenerateOverlapEvents(true);
	CollisionBox -> OnComponentBeginOverlap.AddDynamic(this, &AShipController::OnTriggerEnter);
	
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

	InputComponent -> BindAction("Shoot", IE_Pressed, this, &AShipController::OnShoot);
}

void AShipController::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue * 100.0f;
}

void AShipController::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}

void AShipController::OnShoot()
{
	UE_LOG(LogTemp, Warning, TEXT("SHOOTING"))
	UWorld* World = GetWorld();

	if (World)
	{
		FVector Location = GetActorLocation();
		Location.X += 25;
		World -> SpawnActor<ABulletController>(BulletBP, Location, FRotator::ZeroRotator);
	}
}

void AShipController::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor -> IsA(AEnemyController::StaticClass()))
	{
		Died = true;
		this -> SetActorHiddenInGame(true);

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

