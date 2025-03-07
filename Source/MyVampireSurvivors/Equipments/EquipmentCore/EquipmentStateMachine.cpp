// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentStateMachine.h"

UEquipmentStateMachine::UEquipmentStateMachine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UEquipmentStateMachine::IsReady() const
{
	return CurrentState == EEquipmentState::Ready;
}

void UEquipmentStateMachine::TransitionReadyToInUse()
{
	if (CurrentState == EEquipmentState::Ready)
	{
		CurrentState = EEquipmentState::InUse;
	}
}

void UEquipmentStateMachine::TransitionInUseToCooldown()
{
	if (CurrentState == EEquipmentState::InUse)
	{
		CurrentState = EEquipmentState::Cooldown;
	}
}

void UEquipmentStateMachine::TransitionCooldownToReady()
{
	if (CurrentState == EEquipmentState::Cooldown)
	{
		CurrentState = EEquipmentState::Ready;
		OnEquipmentReady.Broadcast();
	}
}
