// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyVamSurPlayerState.generated.h"

class UExpData;
class UHealthData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStateChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterLevelUp);

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
	FOnCharacterLevelUp OnCharacterLevelUp;

private:
	UFUNCTION()
	void HandlePlayerStateChanged();

	void UnInitializeExpDataDelegates();

private:
	UPROPERTY(Transient)
	TObjectPtr<const UHealthData> HealthData;

public:
	void BindHealthData(const UHealthData* NewHealthData);
	void UnBindHealthData();

	float GetHpRatio() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<const UExpData> ExpData;

public:
	void BindExpData(const UExpData* NewExpData);
	void UnBindExpData();
	float GetExpRatio() const;

private:
	UFUNCTION()
	void HandleCharacterLevelUp();
};
