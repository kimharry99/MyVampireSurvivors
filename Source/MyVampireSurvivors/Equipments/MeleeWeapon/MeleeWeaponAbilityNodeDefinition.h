// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentData/EquipmentAbilityNodeDefinition.h"
#include "Equipments/EquipmentCore/EquipmentAnimationData.h"
#include "MeleeWeaponAbilityNodeDefinition.generated.h"

class UPaperFlipbook;

UENUM(BlueprintType)
enum class EMeleeWeaponOverwrittenStatType : uint8
{
	None				UMETA(DisplayName = "None"),
	AnimationData		UMETA(DisplayName = "Animation Data"),
};

USTRUCT(BlueprintType)
struct FMeleeWeaponStatOverwriteData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Overwrite")
	EMeleeWeaponOverwrittenStatType StatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Overwrite", meta = (EditCondition = "StatType == EMeleeWeaponOverwrittenStatType::AnimationData"))
	FEquipmentAnimationData NewAnimationData;
};

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UMeleeWeaponAbilityNodeDefinition : public UEquipmentAbilityNodeDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	int Damage = 0;

	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	float DamageMultiplier = 0.0f;

	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	float AttackSpeed = 0.0f;

	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	float AttackSpeedMultiplier = 0.0f;

	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	float HitboxMultiplier = 0.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Overwriting Status")
	TArray<FMeleeWeaponStatOverwriteData> OverwriteDataArray;
};
