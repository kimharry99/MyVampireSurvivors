// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMap.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AToroidalMap::AToroidalMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BackgroundComponent = CreateDefaultSubobject<UToroidalMapBackgroundComponent>(TEXT("Background Component"));

	// Set the background to XY plane
	BackgroundComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	RootComponent = BackgroundComponent;
}

// Called when the game starts or when spawned
void AToroidalMap::BeginPlay()
{
	Super::BeginPlay();
}

const FBox AToroidalMap::GetMapRange() const
{
	return BackgroundComponent->GetBackgroundBoundingBox();
}
