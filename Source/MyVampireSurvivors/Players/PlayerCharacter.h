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
class UMyVamSurCameraComponent;
class UPlayerPawnComponent;
class UPlayerCharacterWidget;
class URewardManager;
class UToroidalActorComponent;
class UToroidalPlayerComponent;

/**
 * Player character class.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API APlayerCharacter : public AMyVamSurCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:
	/**
	 * Get the view box of the camera.
	 *
	 * @return The view box of the camera.
	 */
	const FBox GetViewBox() const;

	void InitializeCharacterExp();
	void AddExp(int GainedExp);

	const UExpData* GetExpData() const;

	/**
	 * Add a toroidal actor component that needs to be ticked after the player character.
	 */
	void AddTickSubsequentToroidalComponent(UToroidalActorComponent* Component);

	const UEquipmentInventoryComponent* GetInventoryComponent() const;

	/**
	 * Equip a equipment to the player character.
	 * Add the equipment to the inventory.
	 * The equipment actor will be attached to the player character.
	 *
	 * @param EquipmentClass Equipment to equip.
	 */
	void EquipEquipment(TSubclassOf<AEquipment> EquipmentClass);

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndpPlayReason) override;
	//~End of AActor interface

private:
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMyVamSurCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerCharacterWidget> HPBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = UI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> HPBarWidget;

	void CreateHPBarWidget();

	UPROPERTY()
	TObjectPtr<UExpData> CharacterExp;

	UFUNCTION()
	void HandleCharacterLevelUp();

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<UPlayerPawnComponent> PlayerPawn;

	UPROPERTY(VisibleAnywhere, Category = "Torus")
	TObjectPtr<UToroidalPlayerComponent> ToroidalPlayer;

	URewardManager* GetRewardManagerFromGameMode() const;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEquipmentInventoryComponent> InventoryComponent;

	UPROPERTY()
	TObjectPtr<UEquipmentAutoActivator> EquipmentActivator;

	// FIXME: Remove this code after testing
	//~Begin of testing code
	UPROPERTY(EditAnywhere, Category = "Testing")
	TArray<TSubclassOf<AEquipment>> Equipments;
	//~End of testing code
};
