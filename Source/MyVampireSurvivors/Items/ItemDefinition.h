// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/IDisplableObject.h"
#include "ItemDefinition.generated.h"

class UPaperSprite;

/**
 * 
 */
UCLASS(Blueprintable, Const)
class MYVAMPIRESURVIVORS_API UItemDefinition : public UDataAsset, public IDisplableObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPaperSprite> Icon;

public:
	//~IDisplableObject interface
	UFUNCTION(BlueprintCallable)
	virtual const FText GetObjectName() const override;

	UFUNCTION(BlueprintCallable)
	virtual const FText GetDescription() const override;

	UFUNCTION(BlueprintCallable)
	virtual const UPaperSprite* GetIcon() const override;
	//~End of IDisplableObject interface
};
