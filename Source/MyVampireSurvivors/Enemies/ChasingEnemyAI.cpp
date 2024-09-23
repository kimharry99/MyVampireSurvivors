// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingEnemyAI.h"
#include "Kismet/GameplayStatics.h"

void AChasingEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void AChasingEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn, 5.0f);
	}
}
