// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/MyVamSurCharacter.h"
#include "Equipments/EquipmentInventory.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;
class UInputMappingContext;
class UInputAction;
class AEquipment;
struct FInputActionValue;

/**
 * Player character class.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API APlayerCharacter : public AMyVamSurCharacter
{
	GENERATED_BODY()

// FIXME: Remove this code after testing
//~Begin of testing code
public:
	UPROPERTY(EditAnywhere, Category="Testing")
	TArray<TSubclassOf<AEquipment>> Equipments;
//~End of testing code

public:
	APlayerCharacter();

	/**
	 * Get the view box of the camera.
	 * 
	 * @return The view box of the camera.
	 */
	const FBox GetViewBox() const;

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~End of AActor interface

	//~ACharacter interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//~End of ACharacter interface

private:
	void Move(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D Directionality = FVector2D::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> IMC_TopDownChar = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IA_Move = nullptr;

private:
	/** Inventory of equipments that the player character has. */
	UPROPERTY()
	FEquipmentInventory Inventory;

public:
	/**
	 * Equip a equipment to the player character.
	 * Add the equipment to the inventory.
	 * The equipment actor will be attached to the player character.
	 * 
	 * @param Equipment Equipment to equip.
	 */
	void EquipEquipment(AEquipment* Equipment); 
};
