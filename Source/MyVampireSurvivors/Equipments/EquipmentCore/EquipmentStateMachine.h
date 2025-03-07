// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipmentStateMachine.generated.h"


UENUM(BlueprintType)
enum class EEquipmentState : uint8
{
    Ready     UMETA(DisplayName = "Ready"),
    InUse     UMETA(DisplayName = "InUse"),
    Cooldown  UMETA(DisplayName = "Cooldown"),
};

/**
 *
 */
UCLASS(ClassGroup = Equipment)
class MYVAMPIRESURVIVORS_API UEquipmentStateMachine : public UObject
{
	GENERATED_BODY()

public:
    UEquipmentStateMachine(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    bool IsReady() const;

    void TransitionReadyToInUse();
    void TransitionInUseToCooldown();
    void TransitionCooldownToReady();

    FSimpleMulticastDelegate OnEquipmentReady;

private:
    EEquipmentState CurrentState = EEquipmentState::Ready;
};
