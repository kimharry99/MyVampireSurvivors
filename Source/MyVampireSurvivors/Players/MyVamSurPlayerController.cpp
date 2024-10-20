// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerController.h"
#include "Players/PlayerCharacter.h"

void AMyVamSurPlayerController::PlayerTick(float DeltaSeconds)
{
	Super::PlayerTick(DeltaSeconds);

	if(APlayerCharacter* PlayerCharacter = GetPawn<APlayerCharacter>())
	{
		PlayerCharacter->UseAllEnableEquipments();
	}
}
