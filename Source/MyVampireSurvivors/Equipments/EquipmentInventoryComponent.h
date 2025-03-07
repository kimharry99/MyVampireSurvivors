// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentInventoryComponent.generated.h"

class AEquipment;
class UEquipmentAutoActivator;

UCLASS()
class MYVAMPIRESURVIVORS_API UEquipmentInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentInventoryComponent();

public:
	/**
	 * Add a equipment to inventory.
	 * The equipment actor will be attached to the owner character.
	 * 
	 * @param EquipmentClass Equipment class to equip.
	 */
	void AddEquipment(TSubclassOf<AEquipment> EquipmentClass);
	void AddEquipmentAndRegister(TSubclassOf<AEquipment> EquipmentClass, UEquipmentAutoActivator* EquipmentActivator);

	void GetAllEquipments(TArray<const AEquipment*>& OutEquipments) const;

private:
	UPROPERTY()
	TArray<TObjectPtr<AEquipment>> EquipmentArray;

	const FName SocketName = FName(TEXT("EquipmentSocket"));

	AEquipment* SpawnEquipment(TSubclassOf<AEquipment>& EquipmentClass);
};
