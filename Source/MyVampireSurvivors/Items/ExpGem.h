// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/PickableItem.h"
#include "ExpGem.generated.h"

class APlayerCharacter;
class UHomingItemMovementComponent;

UCLASS()
class MYVAMPIRESURVIVORS_API AExpGem : public APickableItem
{
	GENERATED_BODY()

public:
	AExpGem();

protected:
	//~AActor interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~End of AActor interface

	//~APickableItem interface
	virtual void OnPicked(APlayerCharacter* PlayerCharacter) override;
	//~End of APickableItem interface

private:
	UPROPERTY(EditDefaultsOnly, Category = Exp, meta = (AllowPrivateAccess = "true"))
	int ExpAmount = 1;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<UHomingItemMovementComponent> HomingItemMovementComponent;
};
