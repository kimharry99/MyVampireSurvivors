// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipment.h"
#include "AnimatedEquipment.generated.h"

class UPaperFlipbookComponent;
class USceneComponent;

class UMyFlipbookNotifierComponent;
struct FEquipmentAnimationData;

/**
 * 
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AAnimatedEquipment : public AEquipment
{
	GENERATED_BODY()

protected:
	AAnimatedEquipment(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	//~IUsable interface
	virtual void Use() override;
	//~End of IUsable interface

protected:
	//~AActor interface
	virtual void PostInitializeComponents() override;
	//~End of AActor interface

private:
	UPROPERTY(VisibleAnywhere, Category = Equipment)
	TObjectPtr<USceneComponent> EquipmentRootComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Equipment)
	TObjectPtr<UPaperFlipbookComponent> FlipbookComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Equipment)
	TObjectPtr<UMyFlipbookNotifierComponent> FlipbookNotifierComponent = nullptr;

	void RegisterAnimationDelegates();
	void BindFlipbookToNotifier();

	void OnAnimationChanged(const FEquipmentAnimationData& NewAnimationData);
	void OnAnimationSizeChanged(const float NewSize);
};
