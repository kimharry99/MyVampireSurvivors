// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVamSurGameMode.h"
#include "EngineUtils.h"
#include "ToroidalMaps/ToroidalMap.h"
#include "ToroidalMaps/ToroidalWorldSystem.h"


void AMyVamSurGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	AddToroidalWorldSystemToGame();
}

void AMyVamSurGameMode::AddToroidalWorldSystemToGame()
{
	UWorld* World = GetWorld();
	check(World);

	ToroidalWorldSystem = NewObject<UToroidalWorldSystem>(World);
	for (TActorIterator<AToroidalMap> It(World); It; ++It)
	{
		ToroidalWorldSystem->Initialize(*It);
		break;
	}
}

UToroidalWorldSystem* AMyVamSurGameMode::GetToroidalWorldSystem() const
{
	return ToroidalWorldSystem;
}
