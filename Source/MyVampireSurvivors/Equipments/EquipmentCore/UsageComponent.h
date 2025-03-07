// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UsageComponent.generated.h"

class UPaperFlipbookComponent;

class UMyFlipbookNotifierComponent;
class UStatComponent;

UCLASS(ClassGroup = "Equipment", Abstract)
class MYVAMPIRESURVIVORS_API UUsageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUsageComponent();

public:
	void ExecuteUse(UStatComponent* StatComponent);
	void ExecuteUse(UStatComponent* StatComponent, UPaperFlipbookComponent* FlipbookComponent, UMyFlipbookNotifierComponent* NotifierComponent);

	FSimpleMulticastDelegate OnEquipmentUseInitiated;
	FSimpleMulticastDelegate OnEquipmentUseCompleted;

private:
	virtual void ExecuteUseInternal(UStatComponent* StatComponent);
	virtual void ExecuteUseInternal(UStatComponent* StatComponent, UPaperFlipbookComponent* FlipbookComponent, UMyFlipbookNotifierComponent* NotifierComponent);
};
