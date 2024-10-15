// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalPlayerComponent.h"

void UToroidalPlayerComponent::RepositionActor()
{
	Super::RepositionActor();

	WrapActorLocation();
}
