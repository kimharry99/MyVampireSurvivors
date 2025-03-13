// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/MyVamSurCharacter.h"
#include "PlayerCharacter.generated.h"

template<class UClass> class TSubclassOf;
class USpringArmComponent;
class UWidgetComponent;

class AEquipment;
class UEquipmentAutoActivator;
class UEquipmentInventoryComponent;
class UExpData;
class UPlayerPawnComponent;
class UPlayerCharacterWidget;
class URewardManager;
class UToroidalCameraComponent;

/**
 * Player character class.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API APlayerCharacter : public AMyVamSurCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndpPlayReason) override;
	//~End of AActor interface

	//~AMyVamSurCharacter interface
	virtual void ReceiveAttack(float DamageAmount, AController* Attacker) override;
	//~End of AMyVamSurCharacter interface

	void AddExp(int GainedExp);

	const UExpData* GetExpData() const;

	const UEquipmentInventoryComponent* GetInventoryComponent() const;

	/**
	 * Equip a equipment to the player character.
	 * Add the equipment to the inventory.
	 * The equipment actor will be attached to the player character.
	 *
	 * @param EquipmentClass Equipment to equip.
	 */
	void EquipEquipment(TSubclassOf<AEquipment> EquipmentClass);

private:
	bool bIsInvincible = false;

	FTimerHandle InvincibilityTimerHandle;
	float InvincibilityDuration = 1.0f;

	UFUNCTION()
	void ResetInvincibility();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UToroidalCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UPlayerCharacterWidget> HPBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = UI)
	TObjectPtr<UWidgetComponent> HPBarWidget;

	void CreateHPBarWidget();

	UPROPERTY()
	TObjectPtr<UExpData> CharacterExp;

	UFUNCTION()
	void HandleCharacterLevelUp();

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<UPlayerPawnComponent> PlayerPawn;

	URewardManager* GetRewardManagerFromGameMode() const;

	UPROPERTY(VisibleAnywhere, Category = Equipment)
	TObjectPtr<UEquipmentInventoryComponent> InventoryComponent;

	UPROPERTY()
	TObjectPtr<UEquipmentAutoActivator> EquipmentActivator;

	// FIXME: Remove this code after testing
	//~Begin of testing code
	UPROPERTY(EditAnywhere, Category = "Testing")
	TArray<TSubclassOf<AEquipment>> Equipments;
	//~End of testing code
};
