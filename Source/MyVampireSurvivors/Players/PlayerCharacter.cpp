// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Players/PlayerPawnComponent.h"
#include "ToroidalMaps/ToroidalPlayerComponent.h"
#include "Equipments/Equipment.h"
#include "Weapons/WeaponInterface.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ToroidalActor"));

	GetSprite()->SetCollisionProfileName(TEXT("NoCollision"));
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	FollowCamera->SetOrthoWidth(1024.0f);

	PlayerPawn = CreateDefaultSubobject<UPlayerPawnComponent>(TEXT("PlayerPawnComponent"));

	ToroidalPlayer = CreateDefaultSubobject<UToroidalPlayerComponent>(TEXT("ToroidalPlayerComponent"));
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ToroidalPlayer->AddTickPrerequisiteComponent(GetCharacterMovement());
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// FIXME: Remove this code after testing
	//~Testing code
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	for (const TSubclassOf<AEquipment>& EquipmentClass : Equipments)
	{
		check(EquipmentClass);
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEquipment* TestingEquipment = GetWorld()->SpawnActor<AEquipment>(EquipmentClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
		check(TestingEquipment);
		EquipEquipment(TestingEquipment);
	}
	//~End of testing code
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const FBox APlayerCharacter::GetViewBox() const
{
	const float OrthoWidth = FollowCamera->OrthoWidth;
	const float AspectRatio = FollowCamera->AspectRatio;

	float HalfHeight = OrthoWidth / (2.0f * AspectRatio);
	float HalfWidth = OrthoWidth / 2.0f;

	const FVector Right = GetActorForwardVector();
	const FVector Up = GetActorRightVector();
	const FVector TopRight = (Right * HalfWidth) + (Up * HalfHeight) + (GetActorUpVector() * 100.0f); // Define z range of the box to +-100.0f
	const FVector BottomLeft = -(Right * HalfWidth) - (Up * HalfHeight) - (GetActorUpVector() * 100.0f);

	return FBox(BottomLeft + GetActorLocation(), TopRight + GetActorLocation());
}

void APlayerCharacter::AddTickSubsequentToroidalComponent(UToroidalActorComponent* Component)
{
	if (Component)
	{
		Component->AddTickPrerequisiteComponent(ToroidalPlayer);
	}
}

void APlayerCharacter::EquipEquipment(AEquipment* Equipment)
{
	check(Equipment);
	Inventory.AddEquipment(Equipment);

	if (UPaperFlipbookComponent* CharacterSprite = GetSprite())
	{
		FName SocketName(TEXT("EquipmentSocket"));
		Equipment->AttachToComponent(CharacterSprite, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	}
}

void APlayerCharacter::UseAllEnableEquipments()
{
	Inventory.UseAllEnableEquipments();
}
