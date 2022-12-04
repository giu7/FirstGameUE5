// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase() :
	score(0),
	speed(4.55f),
	canMove(1),
	itemDescription("Hello World Description!"),
	xp(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/*=============================
* UNREAL METHODS *
=============================*/

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	ShowLogs();
	AddScore(2);
	AddScore(2, true);
	AddScore(2, true, 3);
	// AddScore(1);
	// AddXP();
	ShowLogs();

}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*=============================
* GAME METHODS *
=============================*/
int AItemBase::AddXP()
{
	xp = score * 2;
	return xp;
}

void AItemBase::ShowLogs()
{
	UE_LOG(LogTemp, Warning, TEXT("Score: %d"), score);
	UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), speed);
	UE_LOG(LogTemp, Warning, TEXT("Can Move: %d"), canMove);
	UE_LOG(LogTemp, Warning, TEXT("Item Description: %s"), *itemDescription);
	UE_LOG(LogTemp, Warning, TEXT("XP: %d"), xp);

}

void AItemBase::AddScore(int points, bool canAddBonus, int pointsBonus)
{
	if (canAddBonus)
	{
		score = score + points + pointsBonus;
	}
	else
	{
		score += points;
	}
}