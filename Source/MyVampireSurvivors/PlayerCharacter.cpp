// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APlayerCharacter::APlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-90.0f, -90.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
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

	if (PlayerInputComponent != nullptr)
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
		if (EnhancedInputComponent != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			if (PlayerController != nullptr)
			{
				UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
				if (EnhancedSubsystem != nullptr)
				{
					EnhancedSubsystem->AddMappingContext(IMC_TopDownChar, 1);
					EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
				}
			}
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D Direction = Value.Get<FVector2D>();
		if (Direction.Size() > 0.0f)
		{
			const float LeftRightValue = Direction.X;
			AddMovementInput(FVector(1.0f, 0.0f, 0.0f), LeftRightValue);
			const float UpDownValue = Direction.Y;
			AddMovementInput(FVector(0.0f, -1.0f, 0.0f), UpDownValue);

			Directionality = Direction;
		}
	}
}
