// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

#include "Camera/MyVamSurCameraComponent.h"
#include "Equipments/EquipmentInventoryComponent.h"
#include "Equipments/EquipmentAutoActivator.h"
#include "GameModes/MyVamSurGameMode.h"
#include "MyVamSurLogChannels.h"
#include "Players/ExpData.h"
#include "Players/MyVamSurPlayerController.h"
#include "Players/MyVamSurPlayerState.h"
#include "Players/PlayerPawnComponent.h"
#include "Rewards/RewardManager.h"
#include "ToroidalMaps/ToroidalPlayerComponent.h"
#include "UI/PlayerCharacterWidget.h"


APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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

	InventoryComponent = CreateDefaultSubobject<UEquipmentInventoryComponent>(TEXT("Inventory"));
	EquipmentActivator = CreateDefaultSubobject<UEquipmentAutoActivator>(TEXT("EquipmentActivator"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateHPBarWidget();
	InitializeCharacterExp();

	//FIXME
	for (const TSubclassOf<AEquipment>& EquipmentClass : Equipments)
	{
		InventoryComponent->AddEquipmentAndRegister(EquipmentClass, EquipmentActivator);
	}
	//FIXMEEND
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CharacterExp)
	{
		CharacterExp->OnLevelUp.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CharacterExp = NewObject<UExpData>(this);

	ToroidalPlayer->AddTickPrerequisiteComponent(GetCharacterMovement());
	FollowCamera->AddTickPrerequisiteComponent(ToroidalPlayer);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const FBox APlayerCharacter::GetViewBox() const
{
	return FollowCamera->GetWorldViewBox();
}

void APlayerCharacter::CreateHPBarWidget()
{
	check(HPBarWidgetClass);
	check(HPBarWidget);
	HPBarWidget->SetWidgetClass(HPBarWidgetClass);
	HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));

	UPlayerCharacterWidget* HPBarWidgetInstance = Cast<UPlayerCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	check(HPBarWidgetInstance);
	HPBarWidgetInstance->BindHealthData(GetHealthData());
}

void APlayerCharacter::InitializeCharacterExp()
{
	if (!CharacterExp)
	{
		return;
	}

	CharacterExp->Initialize();
	CharacterExp->OnLevelUp.AddDynamic(this, &APlayerCharacter::HandleCharacterLevelUp);
}

void APlayerCharacter::AddExp(int GainedExp)
{
	if (!CharacterExp)
	{
		return;
	}

	CharacterExp->AddExp(GainedExp);
}

const UExpData* APlayerCharacter::GetExpData() const
{
	return CharacterExp;
}

void APlayerCharacter::HandleCharacterLevelUp()
{
	URewardManager* RewardManager = GetRewardManagerFromGameMode();
	if (RewardManager)
	{
		RewardManager->GiveReward(this);
	}
}

void APlayerCharacter::AddTickSubsequentToroidalComponent(UToroidalActorComponent* Component)
{
	if (Component)
	{
		Component->AddTickPrerequisiteComponent(FollowCamera);
	}
}

URewardManager* APlayerCharacter::GetRewardManagerFromGameMode() const
{
	if (UWorld* World = GetWorld())
	{
		if (AMyVamSurGameMode* GameMode = World->GetAuthGameMode<AMyVamSurGameMode>())
		{
			return GameMode->GetRewardManager();
		}
	}

	return nullptr;
}

const UEquipmentInventoryComponent* APlayerCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
}

void APlayerCharacter::EquipEquipment(TSubclassOf<AEquipment> EquipmentClass)
{
	if (InventoryComponent)
	{
		InventoryComponent->AddEquipmentAndRegister(EquipmentClass, EquipmentActivator);
	}
}
