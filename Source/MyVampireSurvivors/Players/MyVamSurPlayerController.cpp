// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerController.h"

#include "Players/PlayerCharacter.h"
#include "Players/MyVamSurPlayerState.h"
#include "UI/MyVamSurBaseWidget.h"
#include "MyVamSurLogChannels.h"

void AMyVamSurPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateBaseWidget();
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
}

void AMyVamSurPlayerController::ResumeGame()
{
	if (IsPaused())
	{
		SetPause(false);
	}
}

void AMyVamSurPlayerController::CreateBaseWidget()
{
	check(BaseWidgetClass);
	BaseWidget = CreateWidget<UMyVamSurBaseWidget>(this, BaseWidgetClass);
	check(BaseWidget);
	BaseWidget->AddToViewport();
}

URewardMenuWidget* AMyVamSurPlayerController::ActivateRewardMenu()
{
	if (BaseWidget)
	{
		SetPause(true);
		return BaseWidget->DisplayLevelUpMenu();
	}

	return nullptr;
}
