// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ToroidalMapManager.h"

APlayerCharacter::APlayerCharacter() : Directionality(FVector2D::ZeroVector)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ToroidalActor"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	FollowCamera->SetOrthoWidth(1024.0f);

	// Initialize the camera view box
	float OrthoWidth = FollowCamera->OrthoWidth;
	float AspectRatio = FollowCamera->AspectRatio;

	float HalfHeight = OrthoWidth / (2.0f * AspectRatio);
	float HalfWidth = OrthoWidth / 2.0f;

	FVector Right = GetActorForwardVector();
	FVector Up = GetActorRightVector();
	FVector TopRight = (Right * HalfWidth) + (Up * HalfHeight) + (GetActorUpVector() * 100.0f); // Define z range of the box to +-100.0f
	FVector BottomLeft = -(Right * HalfWidth) - (Up * HalfHeight) - (GetActorUpVector() * 100.0f);

	CameraViewBox = FBox(BottomLeft, TopRight);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActorLocation = GetActorLocation();
	FVector CurrentBoxCenter = CameraViewBox.GetCenter();
	FVector BoxOffset = ActorLocation - CurrentBoxCenter;

	CameraViewBox = CameraViewBox.ShiftBy(BoxOffset);

	ToroidalMapManager::GetInstance()->HandleMapBoundary(this, CameraViewBox);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent == nullptr) return;
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent == nullptr) return;
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr) return;

	UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (EnhancedSubsystem == nullptr) return;
	
	EnhancedSubsystem->AddMappingContext(IMC_TopDownChar, 1);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
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
