// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletController.h"
#include "EnemyController.h"
#include "SpaceShooterGameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ROOT"));
	RootBox -> SetGenerateOverlapEvents(true);
	RootBox -> OnComponentBeginOverlap.AddDynamic(this, &ABulletController::OnTriggerEnter);

	// UE_LOG(LogTemp, Warning, TEXT("Bullet Initial Location: %f"), GetActorLocation().X)
}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move bullet
	FVector NewLocation = GetActorLocation();
	
	NewLocation.X += Speed * DeltaTime;
	SetActorLocation(NewLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Bullet New Location: %f"), NewLocation.X)
	if(NewLocation.X > 3500.0f)
	{
		this -> Destroy();
	}

}

void ABulletController::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor -> IsA(AEnemyController::StaticClass()))
	{
		this -> Destroy();
		OtherActor -> Destroy();

		((ASpaceShooterGameMode*)GetWorld()->GetAuthGameMode())->IncrementScore();
	}
}

