// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickableItem.h"

#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

#include "Players/PlayerCharacter.h"
#include "ToroidalMaps/ToroidalNPAComponent.h"


APickableItem::APickableItem()
{
	CollisionVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;
	CollisionVolume->SetEnableGravity(false);
	CollisionVolume->SetCollisionProfileName(TEXT("PickableItem"));
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleItemOverlapped);

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);
	Sprite->SetEnableGravity(false);
	Sprite->SetCollisionProfileName(TEXT("NoCollision"));

	ToroidalNPAComponent = CreateDefaultSubobject<UToroidalNPAComponent>(TEXT("ToroidalNPAComponent"));
}

void APickableItem::OnPicked(APlayerCharacter* PlayerCharacter)
{
	Destroy();
}

UToroidalNPAComponent* APickableItem::GetToroidalNPAComponent() const
{
	return ToroidalNPAComponent;
}

void APickableItem::HandleItemOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		OnPicked(PlayerCharacter);
	}
}
