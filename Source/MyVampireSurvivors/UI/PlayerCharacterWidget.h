// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacterWidget.generated.h"

class UProgressBar;

class UHealthData;
class UHealthComponent;

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
	void BindHealthComponent(UHealthComponent* NewHealthComponent);

private:
	UPROPERTY()
	TObjectPtr<const UHealthData> TrackingHealthData;

	TWeakObjectPtr<UHealthComponent> TrackingHealthComponent;

	UPROPERTY()
	TObjectPtr<UProgressBar> HealthBar;

private:
	UFUNCTION()
	void UpdateHealth();
};
