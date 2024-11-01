// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerController.h"

#include "Players/PlayerCharacter.h"
#include "UI/MyVamSurHUDWidget.h"

void AMyVamSurPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(HUDWidgetClass);
	HUDWidget = CreateWidget<UMyVamSurHUDWidget>(this, HUDWidgetClass);
	check(HUDWidget);
	HUDWidget->AddToViewport();

	UWorld* World = GetWorld();
	check(World);
	AGameStateBase* GameState = World->GetGameState();
	check(GameState);
	HUDWidget->BindGameState(GameState);

	check(PlayerState);
	HUDWidget->BindPlayerState(PlayerState);
}

void AMyVamSurPlayerController::PlayerTick(float DeltaSeconds)
{
	Super::PlayerTick(DeltaSeconds);

	if(APlayerCharacter* PlayerCharacter = GetPawn<APlayerCharacter>())
	{
		PlayerCharacter->UseAllEnableEquipments();
	}
}
