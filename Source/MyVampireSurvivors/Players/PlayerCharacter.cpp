// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"

#include "Equipments/EquipmentInventoryComponent.h"
#include "Equipments/EquipmentAutoActivator.h"
#include "GameModes/MyVamSurGameMode.h"
#include "MyVamSurLogChannels.h"
#include "Players/ExpData.h"
#include "Players/MyVamSurPlayerController.h"
#include "Players/MyVamSurPlayerState.h"
#include "Players/PlayerPawnComponent.h"
#include "Rewards/RewardManager.h"
#include "ToroidalMaps/ToroidalActorComponent.h"
#include "ToroidalMaps/ToroidalCameraComponent.h"
#include "UI/PlayerCharacterWidget.h"


APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	check(MoveComp);
	MoveComp->MaxWalkSpeed = 300.0f;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ToroidalActor"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

	GetSprite()->SetCollisionProfileName(TEXT("NoCollision"));
	GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UToroidalCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	FollowCamera->SetOrthoWidth(1024.0f);

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetSprite());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

	CharacterExp = CreateDefaultSubobject<UExpData>(TEXT("CharacterExp"));
	CharacterExp->OnLevelUp.AddDynamic(this, &APlayerCharacter::HandleCharacterLevelUp);

	ToroidalActorComponent = CreateDefaultSubobject<UToroidalActorComponent>(TEXT("ToroidalActorComponent"));
	PlayerPawn = CreateDefaultSubobject<UPlayerPawnComponent>(TEXT("PlayerPawn"));
	
	InventoryComponent = CreateDefaultSubobject<UEquipmentInventoryComponent>(TEXT("Inventory"));
	EquipmentActivator = CreateDefaultSubobject<UEquipmentAutoActivator>(TEXT("EquipmentActivator"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateHPBarWidget();

	check(CharacterExp);
	CharacterExp->InitializeExp();

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

	UHealthData* HPData = GetHealthData();
	check(HPData);
	HPBarWidgetInstance->BindHealthData(HPData);
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

void APlayerCharacter::AddTickSubsequentToroidalComponent(UToroidalActorComponent_Deprecated* Component)
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
