// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacterWidget.generated.h"

class UProgressBar;

class UHealthData;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UPlayerCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//~UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//~End of UUserWidget interface

public:
	void BindHealthData(UHealthData* NewHealthData);

private:
	TWeakObjectPtr<UHealthData> TrackingHealthData;

	UPROPERTY()
	TObjectPtr<UProgressBar> HealthBar;

private:
	UFUNCTION()
	void UpdateHealth();
};
