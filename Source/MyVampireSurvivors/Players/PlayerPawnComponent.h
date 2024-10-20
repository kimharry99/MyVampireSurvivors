// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerPawnComponent.generated.h"

class APawn;
class UInputAction;
class UInputComponent;
class UInputMappingContext;

struct FInputActionValue;

UCLASS()
class MYVAMPIRESURVIVORS_API UPlayerPawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerPawnComponent();

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

private:
	template<typename T>
	FORCEINLINE T* GetPawn() const
	{
		return Cast<T>(GetOwner());
	}

	template<typename T>
	FORCEINLINE T* GetController() const
	{
		if (APawn* Pawn = GetPawn<APawn>())
		{
			return Pawn->GetController<T>();
		}

		return nullptr;
	}

private:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_TopDownChar = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Move = nullptr;

private:
	/**
	 * Initialize player input.
	 * Bind input actions and axis to functions.
	 * 
	 * @param PlayerInputComponent The input component to bind input actions and axis.
	 */
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);

	/**
	 * Move the owner player.
	 * 
	 * @param Value The input action value.
	 */
	void Move(const FInputActionValue& Value);
};
