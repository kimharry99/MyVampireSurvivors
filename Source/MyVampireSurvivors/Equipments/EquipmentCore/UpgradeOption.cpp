// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeOption.h"

UUpgradeOption::UUpgradeOption()
{

}

const FText UUpgradeOption::GetObjectName() const
{
	return FText();
}

const FText UUpgradeOption::GetDescription() const
{
	return FText();
}

const UPaperSprite* UUpgradeOption::GetIcon() const
{
	return nullptr;
}

bool UUpgradeOption::IsActive() const
{
	return false;
}

AEquipment* UUpgradeOption::GetOwningEquipment() const
{
	return nullptr;
}
