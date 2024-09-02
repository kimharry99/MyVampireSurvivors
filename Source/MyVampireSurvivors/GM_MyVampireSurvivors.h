// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemyWaveManager.h"
#include "GM_MyVampireSurvivors.generated.h"

/**
 *
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AGM_MyVampireSurvivors : public AGameModeBase
{
	GENERATED_BODY()

protected:
	/**
	 * Find a toroidal map in the level and initialize the toroidal map manager.
	 */
	virtual void StartPlay() override;
};
