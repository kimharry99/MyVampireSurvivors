// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatedEquipment.h"

#include "PaperFlipbookComponent.h"

#include "EquipmentAnimationData.h"
#include "IEquipmentAnimationStats.h"
#include "MyFlipbookNotifierComponent.h"
#include "MyVamSurLogChannels.h"
#include "StatComponent.h"
#include "UsageComponent.h"

AAnimatedEquipment::AAnimatedEquipment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	EquipmentRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Equipment Root"));
	RootComponent = EquipmentRootComponent;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper Flipbook"));
	FlipbookComponent->SetupAttachment(RootComponent);
	FlipbookComponent->SetVisibility(false);
	FlipbookComponent->SetCollisionProfileName(TEXT("NoCollision"));
	FlipbookComponent->SetLooping(false);

	FlipbookNotifierComponent = CreateDefaultSubobject<UMyFlipbookNotifierComponent>(TEXT("Flipbook Notifier"));
}

void AAnimatedEquipment::Use()
{
	if (!IsUsable())
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Unusable equipment is used: %s"), *GetName());
		return;
	}

	if (UUsageComponent* UsageComp = GetUsageComponent())
	{
		UsageComp->ExecuteUse(GetStatComponent(), FlipbookComponent, FlipbookNotifierComponent);
	}
}

void AAnimatedEquipment::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RegisterAnimationDelegates();
	BindFlipbookToNotifier();
}

void AAnimatedEquipment::RegisterAnimationDelegates()
{
	if (IEquipmentAnimationStats* AnimationStat = Cast<IEquipmentAnimationStats>(GetStatComponent()))
	{
		AnimationStat->AddAnimationChangeEventListener(FOnAnimationChanged::FDelegate::CreateUObject(this, &ThisClass::OnAnimationChanged));
		AnimationStat->AddAnimationSizeChangeEventListener(FOnAnimationSizeChanged::FDelegate::CreateUObject(this, &ThisClass::OnAnimationSizeChanged));
	}
}

void AAnimatedEquipment::BindFlipbookToNotifier()
{
	if (!FlipbookNotifierComponent)
	{
		return;
	}

	FlipbookNotifierComponent->SetFlipbookComponent(FlipbookComponent);
}

void AAnimatedEquipment::OnAnimationChanged(const FEquipmentAnimationData& NewAnimationData)
{
	if (FlipbookComponent)
	{
		FlipbookComponent->SetFlipbook(NewAnimationData.Flipbook);
		FlipbookComponent->SetRelativeLocation(NewAnimationData.FlipbookOffset);
	}

	if (FlipbookNotifierComponent)
	{
		FlipbookNotifierComponent->SetNotifyFrame(NewAnimationData.NotifyKeyFrame);
	}
}

void AAnimatedEquipment::OnAnimationSizeChanged(const float NewSize)
{
	if (FlipbookComponent)
	{
		FlipbookComponent->SetRelativeScale3D(FVector(NewSize));
	}
}
