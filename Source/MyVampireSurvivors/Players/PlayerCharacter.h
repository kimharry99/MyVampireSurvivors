// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "PaperZDCharacter.h"
#include "Characters/MyVamSurCharacter.h"
#include "Equipments/Equipment.h"
#include "Equipments/EquipmentInventory.h"
#include "PlayerCharacter.generated.h"

/**
 * 
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D Directionality;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_TopDownChar;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;

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
