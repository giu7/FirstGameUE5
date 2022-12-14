// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTGAMEUE5_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

	float MIN_INTERVAL = 0.5f;
	float MAX_INTERVAL = 2.0f;
	float TIME_TO_MIN_INTERVAL = 30.0f;

public:
	ASpaceShooterGameMode();
	
	virtual void BeginPlay() override;;

	virtual void Tick(float DeltaSeconds) override;

	void IncrementScore();

	void OnGameOver();

	UPROPERTY(EditAnywhere, Category="Spawning")
	TSubclassOf<AEnemyController> EnemyBlueprint;

	float EnemyTimer;
	float GameTimer;

	UFUNCTION(BlueprintCallable, Category="UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	int Score = 0;

	UPROPERTY(EditAnywhere, Category="UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

};
