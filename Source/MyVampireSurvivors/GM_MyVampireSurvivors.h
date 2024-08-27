// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_MyVampireSurvivors.generated.h"

/**
 *
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AGM_MyVampireSurvivors : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void StartPlay() override;
};
