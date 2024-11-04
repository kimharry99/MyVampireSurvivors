// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyVamSurPlayerState.generated.h"

class UExpData;
class UHealthData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStateChanged);

UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMyVamSurPlayerState();

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

public:
	FOnPlayerStateChanged OnPlayerStateChanged;

private:
	UFUNCTION()
	void HandlePlayerStateChanged();

private:
	UPROPERTY(Transient)
	TObjectPtr<const UHealthData> HealthData;

public:
	void BindHealthData(const UHealthData* NewHealthData);

	float GetHpRatio() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<const UExpData> ExpData;

public:
	void BindExpData(const UExpData* NewExpData);
	float GetExpRatio() const;

private:
	void UnInitializeExpDataDelegates();
};
