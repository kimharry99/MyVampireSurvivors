// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemDefinition.h"

const FText UItemDefinition::GetObjectName() const
{
	return Name;
}

const FText UItemDefinition::GetDescription() const
{
	return Description;
}

const UPaperSprite* UItemDefinition::GetIcon() const
{
	return Icon;
}
