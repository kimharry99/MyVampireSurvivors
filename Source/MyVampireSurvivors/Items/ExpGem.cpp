// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ExpGem.h"

#include "Players/MyVamSurPlayerController.h"
#include "Players/PlayerCharacter.h"

void AExpGem::OnPicked(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->AddExp(ExpAmount);

	Super::OnPicked(PlayerCharacter);
}
