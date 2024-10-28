// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipments/EquipmentInventory.h"
#include "EquipmentComponent.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();

public:
	/**
	 * Add a equipment to inventory.
	 * The equipment actor will be attached to the owner character.
	 * 
	 * @param Equipment Equipment to equip.
	 */
	void AddEquipmentItem(AEquipmentItem* Equipment);

	/**
	 * Use all enable equipments in the inventory.
	 */
	void UseAllEnableEquipments();

private:
	UPROPERTY()
	FEquipmentInventory Inventory;

	const FName SocketName = FName(TEXT("EquipmentSocket"));

	// FIXME: Remove this code after testing
	//~Begin of testing code
public:
	UPROPERTY(EditAnywhere, Category = "Testing")
	TArray<TSubclassOf<AEquipmentItem>> Equipments;

protected:
	virtual void BeginPlay() override;
	//~End of testing code
};
