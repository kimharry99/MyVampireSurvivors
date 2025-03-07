// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RewardManager.generated.h"

class UEquipmentRewardData;
class UReward;
class AEquipment;
class AMyVamSurCharacter;
class APlayerCharacter;

UCLASS(Abstract, Blueprintable)
class MYVAMPIRESURVIVORS_API URewardManager : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Give a reward to the character.
	 */
	void GiveReward(AMyVamSurCharacter* RecipientCharacter);

private:
	TArray<UReward*> RewardOptions;
	TWeakObjectPtr<APlayerCharacter> CurrentRecipientPlayerCharacter;

private:
	UFUNCTION()
	void GiveSelectedReward(int SelectedOption);

	void GenerateRewardOptions(OUT TArray<UReward*>& OutRewardOptions, APlayerCharacter* RecipientCharacter, int OptionCount);

private:
	const AEquipment* FindEquipmentInstance(TArray<const AEquipment*>& AttachedEquipments, TSubclassOf<AEquipment> Target) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UEquipmentRewardData>> EquipmentRewardDatas;
};
