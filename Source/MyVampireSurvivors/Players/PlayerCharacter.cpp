// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

const UCameraComponent* APlayerCharacter::GetFollowCamera() const
{
	return FollowCamera;
}

float APlayerCharacter::GetCameraOrthoWidth() const
{
	return FollowCamera->OrthoWidth;
}

float APlayerCharacter::GetCameraAspectRatio() const
{
	return FollowCamera->AspectRatio;
}

const FBox APlayerCharacter::GetViewBox() const
{
	float HalfHeight = GetCameraOrthoWidth() / (2.0f * GetCameraAspectRatio());
	float HalfWidth = GetCameraOrthoWidth() / 2.0f;

	const FVector Right = GetActorForwardVector();
	const FVector Up = GetActorRightVector();
	const FVector TopRight = (Right * HalfWidth) + (Up * HalfHeight) + (GetActorUpVector() * 100.0f); // Define z range of the box to +-100.0f
	const FVector BottomLeft = -(Right * HalfWidth) - (Up * HalfHeight) - (GetActorUpVector() * 100.0f);

	return FBox(BottomLeft + GetActorLocation(), TopRight + GetActorLocation());
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
