// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/MyVamSurCharacter.h"
#include "Equipments/EquipmentInventory.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UPlayerPawnComponent;
class USpringArmComponent;
class UToroidalActorComponent;
class UToroidalPlayerComponent;
class AEquipment;

/**
 * Player character class.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API APlayerCharacter : public AMyVamSurCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

private:
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	//~End of AActor interface

private:
	UPROPERTY(VisibleAnywhere, Category="Player")
	TObjectPtr<UPlayerPawnComponent> PlayerPawn;

private:
	UPROPERTY(VisibleAnywhere, Category="Torus")
	TObjectPtr<UToroidalPlayerComponent> ToroidalPlayer;

public:
	/**
	 * Add a toroidal actor component that needs to be ticked after the player character.
	 */
	void AddTickSubsequentToroidalComponent(UToroidalActorComponent* Component);

	// FIXME: Remove this code after testing
	//~Begin of testing code
public:
	UPROPERTY(EditAnywhere, Category = "Testing")
	TArray<TSubclassOf<AEquipment>> Equipments;
	//~End of testing code

private:
	/** Inventory of equipments that the player character has. */
	UPROPERTY()
	FEquipmentInventory Inventory;

public:
	/**
	 * Use all enable equipments in the inventory.
	 */
	void UseAllEnableEquipments();

public:
	/**
	 * Equip a equipment to the player character.
	 * Add the equipment to the inventory.
	 * The equipment actor will be attached to the player character.
	 * 
	 * @param Equipment Equipment to equip.
	 */
	void EquipEquipment(AEquipment* Equipment);

public:
	/**
	 * Get the view box of the camera.
	 *
	 * @return The view box of the camera.
	 */
	const FBox GetViewBox() const;

};
