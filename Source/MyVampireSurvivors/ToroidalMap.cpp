// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMap.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/Engine.h"
#include "PlayerCharacter.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"
#include "FileHelpers.h"

// Sets default values
AToroidalMap::AToroidalMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BackgroundComponent = CreateDefaultSubobject<UToroidalMapBackgroundComponent>(TEXT("Background Component"));

	// Set the background to XY plane
	BackgroundComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	BackgroundComponent->SetBackgroundTileMap(BackgroundTileMap);
	RootComponent = BackgroundComponent;

	ToroidalSpaceComponent = CreateDefaultSubobject<UToroidalSpaceComponent>(TEXT("Toroidal Space Component"));
	ToroidalSpaceComponent->SetSpaceBoundary(BackgroundComponent->GetBackgroundBoundingBox());
}

// Called when the game starts or when spawned
void AToroidalMap::BeginPlay()
{
	Super::BeginPlay();
}

void AToroidalMap::HandleMapBoundary(APlayerCharacter* PlayerCharacter) const
{
	ToroidalSpaceComponent->RepositionActorsInToroidalSpace(PlayerCharacter);
}

const FBox AToroidalMap::GetMapRange() const
{
	return BackgroundComponent->GetBackgroundBoundingBox();
}

void AToroidalMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (IsBackgroundTileMapChanged(PropertyChangedEvent))
	{
		BackgroundComponent->SetBackgroundTileMap(BackgroundTileMap);
		ToroidalSpaceComponent->SetSpaceBoundary(BackgroundComponent->GetBackgroundBoundingBox());
	}
}

bool AToroidalMap::IsBackgroundTileMapChanged(FPropertyChangedEvent& PropertyChangedEvent) const
{
	if (PropertyChangedEvent.Property == nullptr)
	{
		return false;
	}

	const FName PropertyName = PropertyChangedEvent.Property->GetFName();
	return PropertyName == GET_MEMBER_NAME_CHECKED(AToroidalMap, BackgroundTileMap);
}
