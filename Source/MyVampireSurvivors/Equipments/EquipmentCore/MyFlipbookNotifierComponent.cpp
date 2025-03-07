// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFlipbookNotifierComponent.h"

#include "PaperFlipbookComponent.h"

UMyFlipbookNotifierComponent::UMyFlipbookNotifierComponent()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMyFlipbookNotifierComponent::BeginPlay()
{
	Super::BeginPlay();


	if (!FlipbookComponent.IsValid())
	{
		if (AActor* Owner = GetOwner())
		{
			FlipbookComponent = Owner->FindComponentByClass<UPaperFlipbookComponent>();
		}
	}
}

void UMyFlipbookNotifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!FlipbookComponent.IsValid())
	{
		return;
	}

	const int CurrentFrame = FlipbookComponent->GetPlaybackPositionInFrames();
	if (CurrentFrame >= NotifyFrame)
	{
		if (OnFrameNotify.IsBound())
		{
			OnFrameNotify.Broadcast();
		}
		OnFrameNotify.Clear();
	}
}

void UMyFlipbookNotifierComponent::AddOnceEventListener(const FOnFrameNotify::FDelegate& Listener)
{
	OnFrameNotify.Add(Listener);
}

void UMyFlipbookNotifierComponent::SetNotifyFrame(int NewNotifyFrame)
{
	NotifyFrame = NewNotifyFrame;
}

void UMyFlipbookNotifierComponent::SetFlipbookComponent(const UPaperFlipbookComponent* NewFlipbookComponent)
{
	if (FlipbookComponent == NewFlipbookComponent)
	{
		return;
	}

	FlipbookComponent = NewFlipbookComponent;
}
