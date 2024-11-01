// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

#include "Camera/MyVamSurCameraComponent.h"
#include "Equipments/EquipmentComponent.h"
#include "Players/MyVamSurPlayerState.h"
#include "Players/PlayerPawnComponent.h"
#include "ToroidalMaps/ToroidalPlayerComponent.h"
#include "UI/PlayerCharacterWidget.h"

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

	FollowCamera = CreateDefaultSubobject<UMyVamSurCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	FollowCamera->SetOrthoWidth(1024.0f);

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetSprite());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	PlayerPawn = CreateDefaultSubobject<UPlayerPawnComponent>(TEXT("PlayerPawn"));

	ToroidalPlayer = CreateDefaultSubobject<UToroidalPlayerComponent>(TEXT("ToroidalPlayer"));

	Inventory = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Inventory"));
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ToroidalPlayer->AddTickPrerequisiteComponent(GetCharacterMovement());
	FollowCamera->AddTickPrerequisiteComponent(ToroidalPlayer);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HPBarWidgetClass);
	check(HPBarWidget);
	HPBarWidget->SetWidgetClass(HPBarWidgetClass);
	HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));

	if (AMyVamSurPlayerState* MyVamSurPlayerState = GetPlayerState<AMyVamSurPlayerState>())
	{
		UPlayerCharacterWidget* HPBarWidgetInstance = Cast<UPlayerCharacterWidget>(HPBarWidget->GetUserWidgetObject());
		check(HPBarWidgetInstance);

		HPBarWidgetInstance->BindHealthData(MyVamSurPlayerState->GetHealthData());
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const FBox APlayerCharacter::GetViewBox() const
{
	return FollowCamera->GetWorldViewBox();
}

void APlayerCharacter::AddTickSubsequentToroidalComponent(UToroidalActorComponent* Component)
{
	if (Component)
	{
		Component->AddTickPrerequisiteComponent(FollowCamera);
	}
}

void APlayerCharacter::EquipEquipment(AEquipmentItem* Equipment)
{
	Inventory->AddEquipmentItem(Equipment);
}

void APlayerCharacter::UseAllEnableEquipments()
{
	Inventory->UseAllEnableEquipments();
}
