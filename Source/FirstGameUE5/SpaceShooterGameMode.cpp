// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"

#include "GameWidget.h"
#include "Blueprint/UserWidget.h"

ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);
	((UGameWidget*)CurrentWidget)->Load();
	
}

void ASpaceShooterGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GameTimer += DeltaSeconds;
	EnemyTimer -= DeltaSeconds;

	if (EnemyTimer <= 0.0f)
	{
		float DifficultyPercentage = FMath::Min(GameTimer/MIN_INTERVAL, 1.0f);
		EnemyTimer = MAX_INTERVAL - (MAX_INTERVAL - MIN_INTERVAL) * DifficultyPercentage;

		UE_LOG(LogTemp, Warning, TEXT("Timer is %f"), EnemyTimer);

		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = FVector(3300.0f, FMath::RandRange(2700.0f, 5000.0f), 67.0f);
			World -> SpawnActor<AEnemyController>(EnemyBlueprint, Location, FRotator::ZeroRotator);
		}
		
	}
}

void ASpaceShooterGameMode::IncrementScore()
{
	Score += 100;
	UE_LOG(LogTemp, Warning, TEXT("Score updated %d"), Score);
	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void ASpaceShooterGameMode::OnGameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}

void ASpaceShooterGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
