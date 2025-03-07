// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentData/EquipmentAbilityNodeDefinition.h"
#include "LauncherAbilityNodeDefinition.generated.h"

class AProjectileWeapon;
class UProjectileSpawnStrategy;

UENUM(BlueprintType)
enum class ELauncherOverwrittenStatType : uint8
{
	None			UMETA(DisplayName = "None"),
	Projectile		UMETA(DisplayName = "Projectile"),
	SpawnStrategy	UMETA(DisplayName = "Spawn Strategy")
};

USTRUCT(BlueprintType)
struct FLauncherStatOverwriteData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Overwrite")
	ELauncherOverwrittenStatType StatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Overwrite", meta = (EditCondition = "StatType == ELauncherOverwrittenStatType::Projectile"))
	TSubclassOf<AProjectileWeapon> ProjectileWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat Overwrite", meta = (EditCondition = "StatType == ELauncherOverwrittenStatType::SpawnStrategy"))
	TSubclassOf<UProjectileSpawnStrategy> SpawnStrategyClass;
};

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API ULauncherAbilityNodeDefinition : public UEquipmentAbilityNodeDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	float AttackSpeed = 0.0f;

	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	float AttackSpeedMultiplier = 0.0f;

	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	int ProjectileCount = 0;

	UPROPERTY(EditInstanceOnly, Category = "Additional Status")
	float ProjectileSpeed = 0.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Overwriting Status")
	TArray<FLauncherStatOverwriteData> OverwriteDataArray;
};
