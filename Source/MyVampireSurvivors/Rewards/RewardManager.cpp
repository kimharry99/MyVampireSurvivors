// Fill out your copyright notice in the Description page of Project Settings.

#include "Rewards/RewardManager.h"

#include "Characters/MyVamSurCharacter.h"
#include "Equipments/EquipmentCore/Equipment.h"
#include "Equipments/EquipmentInventoryComponent.h"
#include "MyVamSurLogChannels.h"
#include "Players/MyVamSurPlayerController.h"
#include "Players/PlayerCharacter.h"
#include "Rewards/EquipmentRewardData.h"
#include "Rewards/Reward.h"
#include "Rewards/RewardFactory.h"
#include "UI/RewardMenuWidget.h"

void URewardManager::GiveReward(AMyVamSurCharacter* RecipientCharacter)
{
	// Get the player controller from the recipient character
	AMyVamSurPlayerController* PlayerController = RecipientCharacter->GetController<AMyVamSurPlayerController>();
	if (PlayerController)
	{
		// Activate the reward menu UI
		URewardMenuWidget* RewardMenuWidget = PlayerController->ActivateRewardMenu();
		if (RewardMenuWidget)
		{
			// Set the current recipient player character
			CurrentRecipientPlayerCharacter = Cast<APlayerCharacter>(RecipientCharacter);
			if (CurrentRecipientPlayerCharacter.IsValid())
			{
				// Generate reward options based on the number of options available in the UI
				int OptionCount = RewardMenuWidget->GetOptionCount();
				GenerateRewardOptions(RewardOptions, CurrentRecipientPlayerCharacter.Get(), OptionCount);

				// Update the reward menu UI with the generated options
				RewardMenuWidget->UpdateOptions(RewardOptions);

				// Bind the callback function for when a reward option is selected
				FOnMenuOptionSelected CallBack;
				CallBack.BindDynamic(this, &URewardManager::GiveSelectedReward);
				RewardMenuWidget->SetOptionSelectedCallBack(CallBack);
			}
		}
	}
}

void URewardManager::GiveSelectedReward(int SelectedOption)
{
	if (!CurrentRecipientPlayerCharacter.IsValid() || !RewardOptions[SelectedOption])
	{
		return;
	}

	// Apply the selected reward to the current recipient player character
	RewardOptions[SelectedOption]->ApplyReward(CurrentRecipientPlayerCharacter.Get());
}

void URewardManager::GenerateRewardOptions(OUT TArray<UReward*>& OutRewardOptions, APlayerCharacter* RecipientCharacter, int OptionCount)
{
	// Reset the output reward options array
	OutRewardOptions.Reset();

	// Generate and add reward options to the array
	FRewardFactory Factory;

	TArray<const AEquipment*> EquippedItems;
	RecipientCharacter->GetInventoryComponent()->GetAllEquipments(EquippedItems);

	for (UEquipmentRewardData* EquipmentRewardData : EquipmentRewardDatas)
	{
		// Check if the equipment is already equipped
		if (const AEquipment* EquippedItem = FindEquipmentInstance(EquippedItems, EquipmentRewardData->EquipmentClass))
		{
			UE_LOG(LogMyVamSur, Log, TEXT("Generate reward of %s"), *(EquippedItem->GetName()));
			// Create upgrade reward options
			TArray<UUpgradeOption*> UnlockableNodes;
			EquippedItem->GetUpgradeableOptions(UnlockableNodes);

			for (UUpgradeOption* UnlockableNode : UnlockableNodes)
			{
				OutRewardOptions.Add(Factory.CreateReward(this, UnlockableNode));
			}
		}
		else
		{
			// Create equipment reward option
			OutRewardOptions.Add(Factory.CreateReward(this, EquipmentRewardData));
		}
	}

	for (int i = OutRewardOptions.Num(); i < OptionCount; ++i)
	{
		OutRewardOptions.Add(Factory.CreateEmptyReward(this));
	}
}

const AEquipment* URewardManager::FindEquipmentInstance(TArray<const AEquipment*>& AttachedEquipments, TSubclassOf<AEquipment> Target) const
{
	for (const AEquipment* Equipment : AttachedEquipments)
	{
		if (Target == Equipment->GetClass())
		{
			return Equipment;
		}
	}

	return nullptr;
}
