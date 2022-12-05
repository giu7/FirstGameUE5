// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTGAMEUE5_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Load();
	
	void SetScore(int Score);
	void OnGameOver(int Score);

	UPROPERTY()
	UTextBlock* ScoreText;
};
