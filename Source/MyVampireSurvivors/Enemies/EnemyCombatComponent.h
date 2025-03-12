// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyCombatComponent.generated.h"


UCLASS(ClassGroup = "Enemy")
class MYVAMPIRESURVIVORS_API UEnemyCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyCombatComponent(const FObjectInitializer& ObjectInitializer);

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

private:
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> HitPrimitiveComponent;

	void FindHitPrimitiveComponentFromOwnerRoot();

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	int Damage = 1;

	UFUNCTION()
	void HandleEnemyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
