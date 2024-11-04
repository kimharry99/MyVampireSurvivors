// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyVamSurHUDWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "GameModes/MyVamSurGameState.h"
#include "Players/MyVamSurPlayerState.h"

void UMyVamSurHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PBExp = Cast<UProgressBar>(GetWidgetFromName(TEXT("PBExp")));
	check(PBExp);

	TextTime = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextTime")));
	check(TextTime);
}

void UMyVamSurHUDWidget::NativeDestruct()
{
	UnInitializeGameStateDelegates();
	UnInitializePlayerStateDelegates();

	Super::NativeDestruct();
}

void UMyVamSurHUDWidget::BindGameState(AGameStateBase* GameState)
{
	if(AMyVamSurGameState* NewMyVamSurGameState = Cast<AMyVamSurGameState>(GameState))
	{
		UnInitializeGameStateDelegates();

		MyVamSurGameState = NewMyVamSurGameState;
		MyVamSurGameState->OnGameTimeChanged.AddDynamic(this, &UMyVamSurHUDWidget::UpdateTextTime);
		UpdateTextTime(MyVamSurGameState->GetGameTime());
	}
}

void UMyVamSurHUDWidget::BindPlayerState(APlayerState* PlayerState)
{
	if (AMyVamSurPlayerState* NewMyVamsurPlayerState = Cast<AMyVamSurPlayerState>(PlayerState))
	{
		UnInitializePlayerStateDelegates();

		MyVamSurPlayerState = NewMyVamsurPlayerState;
		MyVamSurPlayerState->OnPlayerStateChanged.AddDynamic(this, &UMyVamSurHUDWidget::UpdateExpBar);
		UpdateExpBar();
	}
}

void UMyVamSurHUDWidget::UpdateTextTime(double NewGameTime)
{
	if (TextTime == nullptr)
	{
		return;
	}

	const int Minutes = FMath::Clamp(FMath::FloorToInt(NewGameTime / 60.0), 0, 59);
	const int Seconds = FMath::FloorToInt(FMath::Fmod(NewGameTime, 60.0f));

	const FString TimeText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	TextTime->SetText(FText::FromString(TimeText));
}

void UMyVamSurHUDWidget::UpdateExpBar()
{
	if (PBExp == nullptr)
	{
		return;
	}
	if (MyVamSurPlayerState == nullptr)
	{
		return;
	}

	const float ExpRatio = MyVamSurPlayerState->GetExpRatio();
	PBExp->SetPercent(ExpRatio);
}

void UMyVamSurHUDWidget::UnInitializeGameStateDelegates()
{
	if (MyVamSurGameState == nullptr)
	{
		return;
	}

	MyVamSurGameState->OnGameTimeChanged.RemoveAll(this);
}

void UMyVamSurHUDWidget::UnInitializePlayerStateDelegates()
{
	if (MyVamSurPlayerState == nullptr)
	{
		return;
	}

	MyVamSurPlayerState->OnPlayerStateChanged.RemoveAll(this);
}
