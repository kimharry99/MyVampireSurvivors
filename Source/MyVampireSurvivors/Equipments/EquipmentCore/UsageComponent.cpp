// Fill out your copyright notice in the Description page of Project Settings.


#include "UsageComponent.h"

UUsageComponent::UUsageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUsageComponent::ExecuteUse(UStatComponent* StatComponent)
{
	OnEquipmentUseInitiated.Broadcast();
	ExecuteUseInternal(StatComponent);
	OnEquipmentUseCompleted.Broadcast();
}

void UUsageComponent::ExecuteUse(UStatComponent* StatComponent, UPaperFlipbookComponent* FlipbookComponent, UMyFlipbookNotifierComponent* NotifierComponent)
{
	OnEquipmentUseInitiated.Broadcast();
	ExecuteUseInternal(StatComponent, FlipbookComponent, NotifierComponent);
	OnEquipmentUseCompleted.Broadcast();
}

void UUsageComponent::ExecuteUseInternal(UStatComponent* StatComponent)
{
	// Empty implementation
}

void UUsageComponent::ExecuteUseInternal(UStatComponent* StatComponent, UPaperFlipbookComponent* FlipbookComponent, UMyFlipbookNotifierComponent* NotifierComponent)
{
	// Empty implementation
}
