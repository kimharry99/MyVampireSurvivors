// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "MyVamSurCharacter.generated.h"

class UHealthComponent;

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
	AMyVamSurCharacter();

private:
	/** The character's HealthComponent. */
	UPROPERTY(EditDefaultsOnly, Category="Character|Health")
	TObjectPtr<UHealthComponent> Health;

public:
	/**
	 * Handles the character receiving an attack.
	 * 
	 * @param DamageAmount How much damage to apply
	 * @param Attacker The Controller that attacks the character.
	 */
	virtual void ReceiveAttack(float DamageAmount, AController* Attacker);

private:
	//~AActor interface
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	//~End of AActor interface

public:
	/** Called when the character dies. */
	FOnCharacterDied OnCharacterDied;

protected:
	/**
	 * Handles the character's death.
	 */
	UFUNCTION()
	virtual void StartDeath();
};
