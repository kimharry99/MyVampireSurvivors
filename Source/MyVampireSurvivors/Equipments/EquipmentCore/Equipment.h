// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IUpgradeable.h"
#include "IUsable.h"
#include "Equipment.generated.h"

class AEquipment;
class UEquipmentStateMachine;
class UStatComponent;
class UUsageComponent;
class UUpgradeComponent;
class UUpgradeOption;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipmentUsable, TWeakObjectPtr<AEquipment>);

UCLASS(Abstract, ClassGroup = "Equipment")
class MYVAMPIRESURVIVORS_API AEquipment : public AActor, public IUsable, public IUpgradeable
{
	GENERATED_BODY()

protected:
	AEquipment(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	//~AActor interface
	virtual void PostInitializeComponents() override;
	//~End of AActor interface

	//~IUsable interface
	virtual bool IsUsable() const final override;
	virtual void Use() override;
	//~End of IUsable interface

	//~IUpgradeable interface
	virtual void GetUpgradeableOptions(OUT TArray<UUpgradeOption*>& OutOptions) const final override;
	virtual void Upgrade(UUpgradeOption* UpgradeOption) final override;
	//~End of IUpgradeable interface

	static FName StatComponentName;
	static FName UpgradeComponentName;
	static FName UsageComponentName;

	FOnEquipmentUsable OnEquipmentUsable;

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

	FORCEINLINE UStatComponent* GetStatComponent() const { return StatComponent; };
	FORCEINLINE UUpgradeComponent* GetUpgradeComponent() const { return UpgradeComponent; };
	FORCEINLINE UUsageComponent* GetUsageComponent() const { return UsageComponent; };
	FORCEINLINE UEquipmentStateMachine* GetStateMachine() const { return StateMachine; };

private:
	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TObjectPtr<UStatComponent> StatComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TObjectPtr<UUpgradeComponent> UpgradeComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Equipment")
	TObjectPtr<UUsageComponent> UsageComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UEquipmentStateMachine> StateMachine = nullptr;

	void InitializeStatus();

	void HandleEquipmentReady();
};
