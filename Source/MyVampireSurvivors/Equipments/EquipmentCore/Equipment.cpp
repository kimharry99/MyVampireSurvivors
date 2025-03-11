// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

#include "EquipmentStateMachine.h"
#include "MyVamSurLogChannels.h"
#include "StatComponent.h"
#include "UpgradeComponent.h"
#include "UsageComponent.h"

FName AEquipment::StatComponentName((TEXT("StatComponent")));
FName AEquipment::UpgradeComponentName((TEXT("UpgradeComponent")));
FName AEquipment::UsageComponentName((TEXT("UsageComponent")));

AEquipment::AEquipment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	StatComponent = CreateDefaultSubobject<UStatComponent>(AEquipment::StatComponentName);
	UpgradeComponent = CreateDefaultSubobject<UUpgradeComponent>(AEquipment::UpgradeComponentName);
	UsageComponent = CreateDefaultSubobject<UUsageComponent>(AEquipment::UsageComponentName);

	StateMachine = CreateDefaultSubobject<UEquipmentStateMachine>(TEXT("StateMachine"));
}

void AEquipment::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (StateMachine)
	{
		StateMachine->OnEquipmentReady.Add(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::HandleEquipmentReady));
	}

	if (UsageComponent && StateMachine)
	{
		UsageComponent->OnEquipmentUseInitiated.Add(FSimpleMulticastDelegate::FDelegate::CreateUObject(StateMachine, &UEquipmentStateMachine::TransitionReadyToInUse));
		UsageComponent->OnEquipmentUseCompleted.Add(FSimpleMulticastDelegate::FDelegate::CreateUObject(StateMachine, &UEquipmentStateMachine::TransitionInUseToCooldown));
	}
}

bool AEquipment::IsUsable() const
{
	if (!StateMachine)
	{
		return false;
	}

	return StateMachine->IsReady();
}

void AEquipment::Use()
{
	if (UsageComponent)
	{
		UsageComponent->ExecuteUse(StatComponent);
	}
}

void AEquipment::GetUpgradeableOptions(OUT TArray<UUpgradeOption*>& OutOptions) const
{
	if (UpgradeComponent)
	{
		OutOptions.Append(UpgradeComponent->GetUpgradeableOptions());
	}
}

void AEquipment::Upgrade(UUpgradeOption* UpgradeOption)
{
	if (UpgradeComponent)
	{
		UpgradeComponent->UpgradeStat(StatComponent, UpgradeOption);
	}
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();

	InitializeStatus();
}

void AEquipment::InitializeStatus()
{
	if (UpgradeComponent)
	{
		UpgradeComponent->UpdateStat(StatComponent);
	}
}

void AEquipment::HandleEquipmentReady()
{
	OnEquipmentUsable.Broadcast(this);
}
