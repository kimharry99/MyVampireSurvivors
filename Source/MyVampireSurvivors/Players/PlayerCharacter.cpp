// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PaperFlipbookComponent.h"
#include "ToroidalMaps/ToroidalPlayerComponent.h"
#include "Equipments/Equipment.h"
#include "Weapons/WeaponInterface.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	ToroidalPlayerComponent = CreateDefaultSubobject<UToroidalPlayerComponent>(TEXT("ToroidalPlayerComponent"));
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ToroidalPlayerComponent->AddTickPrerequisiteComponent(GetCharacterMovement());
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

	Inventory.UseAllEnableEquipments();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(EnhancedInputComponent);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController);
	UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	check(EnhancedSubsystem);
	EnhancedSubsystem->AddMappingContext(IMC_TopDownChar, 1);
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

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2D Direction = Value.Get<FVector2D>();
		if (Direction.SizeSquared() > 0.0f)
		{
			const FVector RightDirection = FVector::ForwardVector * Direction.X;
			const FVector UpDirection = -FVector::RightVector * Direction.Y;

			AddMovementInput(RightDirection + UpDirection);

			Directionality = Direction;
		}
	}
}

void APlayerCharacter::AddTickSubsequentToroidalComponent(UToroidalActorComponent* Component)
{
	if (Component)
	{
		Component->AddTickPrerequisiteComponent(ToroidalPlayerComponent);
	}
}

void APlayerCharacter::EquipEquipment(AEquipment* Equipment)
{
	check(Equipment);
	check(GetSprite());
	Inventory.AddEquipment(Equipment);
	FName SocketName(TEXT("EquipmentSocket"));
	Equipment->AttachToComponent(GetSprite(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
}
