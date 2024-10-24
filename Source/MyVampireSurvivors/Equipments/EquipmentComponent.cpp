// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/EquipmentComponent.h"
#include "Equipments/EquipmentItem.h"
#include "PaperFlipbookComponent.h"
#include "Players/PlayerCharacter.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipmentComponent::AddEquipmentItem(AEquipmentItem* Item)
{
	if(Item == nullptr)
	{
		return;
	}

	Inventory.AddEquipment(Item);

	// Attach the equipment to the character sprite.
	if(APlayerCharacter* OwnerCharacter = GetOwner<APlayerCharacter>())
	{
		if (UPaperFlipbookComponent* CharacterSprite = OwnerCharacter->GetSprite())
		{
			Item->AttachToComponent(CharacterSprite, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
		}
	}
}

void UEquipmentComponent::UseAllEnableEquipments()
{
	TArray<AEquipmentItem*> EnableEquipments = Inventory.GetAllEnableEquipments();
	for (AEquipmentItem* Equipment : EnableEquipments)
	{
		Equipment->UseEquipment();
	}
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	// FIXME: Remove this code after testing
	//~Testing code
	APawn* Pawn = GetOwner<APawn>();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Pawn;
	SpawnParams.Instigator = Pawn;

	for (const TSubclassOf<AEquipmentItem>& EquipmentClass : Equipments)
	{
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEquipmentItem* TestingEquipment = GetWorld()->SpawnActor<AEquipmentItem>(EquipmentClass, Pawn->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
		AddEquipmentItem(TestingEquipment);
	}
	//~End of testing code
}
