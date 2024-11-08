// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerController.h"

#include "Players/PlayerCharacter.h"
#include "Players/MyVamSurPlayerState.h"
#include "UI/MyVamSurHUDWidget.h"
#include "MyVamSurLogChannels.h"

void AMyVamSurPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateHUDWidget();

	if (AMyVamSurPlayerState* MyVamSurPlayerState = GetPlayerState<AMyVamSurPlayerState>())
	{
		MyVamSurPlayerState->OnCharacterLevelUp.AddDynamic(this, &AMyVamSurPlayerController::HandleCharacterLevelUp);
	}
}

void AMyVamSurPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AMyVamSurPlayerState* MyVamSurPlayerState = GetPlayerState<AMyVamSurPlayerState>())
	{
		MyVamSurPlayerState->OnCharacterLevelUp.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AMyVamSurPlayerController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PawnToPossess))
	{
		if (AMyVamSurPlayerState* MyVamSurPlayerState = GetPlayerState<AMyVamSurPlayerState>())
		{
			MyVamSurPlayerState->BindHealthData(PlayerCharacter->GetHealthData());
			MyVamSurPlayerState->BindExpData(PlayerCharacter->GetExpData());
		}
	}
}

void AMyVamSurPlayerController::OnUnPossess()
{
	if (AMyVamSurPlayerState* MyVamSurPlayerState = GetPlayerState<AMyVamSurPlayerState>())
	{
		MyVamSurPlayerState->UnBindHealthData();
		MyVamSurPlayerState->UnBindExpData();
	}

	Super::OnUnPossess();
}

void AMyVamSurPlayerController::PlayerTick(float DeltaSeconds)
{
	Super::PlayerTick(DeltaSeconds);

	if(APlayerCharacter* PlayerCharacter = GetPawn<APlayerCharacter>())
	{
		PlayerCharacter->UseAllEnableEquipments();
	}
}

void AMyVamSurPlayerController::ResumeGame()
{
	if (IsPaused())
	{
		SetPause(false);
	}
}

void AMyVamSurPlayerController::CreateHUDWidget()
{
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

void AMyVamSurPlayerController::HandleCharacterLevelUp()
{
	DisplayLevelUpMenu();
}

void AMyVamSurPlayerController::DisplayLevelUpMenu()
{
}
