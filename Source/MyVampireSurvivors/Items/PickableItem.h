// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;

class APlayerCharacter;
class UToroidalActorComponent;

UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:
	APickableItem();

protected:
	virtual void OnPicked(APlayerCharacter* PlayerCharacter);

private:
	UFUNCTION()
	void HandleItemOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

private:
	UPROPERTY(EditDefaultsOnly, Category= "Item")
	TObjectPtr<UCapsuleComponent> CollisionVolume;

	UPROPERTY(EditDefaultsOnly, Category= "Item")
	TObjectPtr<UPaperSpriteComponent> Sprite;

	UPROPERTY(VisibleAnywhere, Category = "ToroidalWorld")
	TObjectPtr<UToroidalActorComponent> ToroidalActorComponent;
};
