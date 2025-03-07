// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/EquipmentInventoryComponent.h"

#include "Equipments/EquipmentAutoActivator.h"
#include "Equipments/EquipmentCore/Equipment.h"
#include "PaperFlipbookComponent.h"
#include "Players/PlayerCharacter.h"

UEquipmentInventoryComponent::UEquipmentInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipmentInventoryComponent::GetAllEquipments(TArray<const AEquipment*>& OutEquipments) const
{
	for (AEquipment* Equipment : EquipmentArray)
	{
		OutEquipments.Add(Equipment);
	}
}

void UEquipmentInventoryComponent::AddEquipment(TSubclassOf<AEquipment> EquipmentClass)
{
	AEquipment* Equipment = SpawnEquipment(EquipmentClass);

	// Add the equipment to the inventory
	EquipmentArray.Add(Equipment);
}

void UEquipmentInventoryComponent::AddEquipmentAndRegister(TSubclassOf<AEquipment> EquipmentClass, UEquipmentAutoActivator* EquipmentActivator)
{
	if (AEquipment* Equipment = SpawnEquipment(EquipmentClass))
	{
		EquipmentArray.Add(Equipment);

		if (EquipmentActivator)
		{
			EquipmentActivator->RegisterAndUseEquipment(Equipment);
		}
	}
}

AEquipment* UEquipmentInventoryComponent::SpawnEquipment(TSubclassOf<AEquipment>& EquipmentClass)
{
	// Spawn Equipment Item
	APawn* Pawn = GetOwner<APawn>();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Pawn;
	SpawnParams.Instigator = Pawn;

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AEquipment* Equipment = GetWorld()->SpawnActor<AEquipment>(EquipmentClass, Pawn->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

	// Attach the equipment to the character sprite
	if (APlayerCharacter* OwnerCharacter = GetOwner<APlayerCharacter>())
	{
		if (UPaperFlipbookComponent* CharacterSprite = OwnerCharacter->GetSprite())
		{
			Equipment->AttachToComponent(CharacterSprite, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
		}
	}

	return Equipment;
}
