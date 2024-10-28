// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVamSurGameMode.h"
#include "EngineUtils.h"
#include "GameModes/MyVamSurGameState.h"
#include "Players/PlayerCharacter.h"
#include "Players/MyVamSurPlayerState.h"
#include "Players/MyVamSurPlayerController.h"
#include "ToroidalMaps/ToroidalMap.h"
#include "ToroidalMaps/ToroidalWorldSystem.h"

AMyVamSurGameMode::AMyVamSurGameMode()
{
	GameStateClass = AMyVamSurGameState::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AMyVamSurPlayerController::StaticClass();
	PlayerStateClass = AMyVamSurPlayerState::StaticClass();
}

void AMyVamSurGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	AddToroidalWorldSystemToGame();
	AddWaveManagerToGame();
}

UToroidalWorldSystem* AMyVamSurGameMode::GetToroidalWorldSystem() const
{
	return ToroidalWorldSystem;
}

void AMyVamSurGameMode::AddToroidalWorldSystemToGame()
{
	// GameMode does not need to check if the world is valid
	UWorld* World = GetWorld();

	ToroidalWorldSystem = NewObject<UToroidalWorldSystem>(World);
	for (TActorIterator<AToroidalMap> It(World); It; ++It)
	{
		ToroidalWorldSystem->Initialize(*It);
		break;
	}
}

void AMyVamSurGameMode::AddWaveManagerToGame()
{
	// GameMode does not need to check if the world is valid
	UWorld* World = GetWorld();

	check(WaveManagerClass);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = GetInstigator();
	WaveManager = World->SpawnActor<AWaveManager>(WaveManagerClass, SpawnParams);

	check(WaveManager);
	AMyVamSurGameState* MyGameState = GetGameState<AMyVamSurGameState>();
	check(MyGameState);
	MyGameState->SetWaveManager(WaveManager);
}
