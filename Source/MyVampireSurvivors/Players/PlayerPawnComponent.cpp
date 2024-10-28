// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values for this component's properties
UPlayerPawnComponent::UPlayerPawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UPlayerPawnComponent::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* Pawn = GetPawn<APawn>())
	{
		if (Pawn->InputComponent != nullptr)
		{
			InitializePlayerInput(Pawn->InputComponent);
		}
	}
}

void UPlayerPawnComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APlayerController* PlayerController = GetController<APlayerController>();
	check(PlayerController);

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	check(LocalPlayer);

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		EnhancedSubsystem->AddMappingContext(IMC_TopDownChar, 1);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &UPlayerPawnComponent::Move);
	}
}

void UPlayerPawnComponent::Move(const FInputActionValue& Value)
{
	APawn* Pawn = GetPawn<APawn>();

	if (Pawn && Pawn->GetController())
	{
		const FVector2D Direction = Value.Get<FVector2D>();
		if (Direction.SizeSquared() > 0.0f)
		{
			const FVector RightDirection = FVector::ForwardVector * Direction.X;
			const FVector UpDirection = -FVector::RightVector * Direction.Y;

			Pawn->AddMovementInput(RightDirection + UpDirection);
		}
	}
}

