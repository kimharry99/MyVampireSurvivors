// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "MyVamSurCharacter.generated.h"

class UHealthData;
class UToroidalActorComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDied);

/**
 * Base class for all characters in the game.
 * The class contains HealthPoint and other related functions.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AMyVamSurCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

	/** Called when the character dies. */
	FOnCharacterDied OnCharacterDied;

	/**
	 * Handles the character receiving an attack.
	 *
	 * @param DamageAmount How much damage to apply
	 * @param Attacker The Controller that attacks the character.
	 */
	virtual void ReceiveAttack(float DamageAmount, AController* Attacker);

protected:
	/**
	 * Handles the character's death.
	 */
	UFUNCTION()
	virtual void StartDeath();

	FORCEINLINE UHealthData* GetHealthData() const { return HealthData; };

	FORCEINLINE float GetDefaultMaxHealth() const { return DefaultMaxHealth; };

	FLinearColor InitialSpriteColor;
	void StartBlinking(const float Duration);
	void BlinkOnce();
	void ToggleBlinking();
	void StopBlinking();

private:
	UPROPERTY()
	TObjectPtr<UHealthData> HealthData;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	float DefaultMaxHealth = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "ToroidalWorld")
	TObjectPtr<UToroidalActorComponent> ToroidalActorComponent;

	static float GROUND_HEIGHT;

	FTimerHandle BlinkingTimerHandle;
	FTimerHandle DurationTimerHandle;

	float BlinkingInterval = 0.08f;
};
