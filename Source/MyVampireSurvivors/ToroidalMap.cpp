// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMap.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AToroidalMap::AToroidalMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BackgroundComponent = CreateDefaultSubobject<UToroidalMapBackgroundComponent>(TEXT("Background Component"));

	// Set the background to XY plane
	BackgroundComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	BackgroundComponent->SetBackgroundTileMap(BackgroundTileMap);
	RootComponent = BackgroundComponent;

	ToroidalSpaceComponent = CreateDefaultSubobject<UToroidalSpaceComponent>(TEXT("Toroidal Space Component"));
}

// Called when the game starts or when spawned
void AToroidalMap::BeginPlay()
{
	Super::BeginPlay();

	// Cache player character reference
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PlayerController)
	{
		PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn());
	}

	ToroidalSpaceComponent->SetSpaceBoundary(BackgroundComponent->GetBackgroundBoundingBox());
}

void AToroidalMap::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleActorsOnToroidalMap();
}

void AToroidalMap::HandleActorsOnToroidalMap() const
{
	ToroidalSpaceComponent->RepositionActorsInToroidalSpace(PlayerCharacter);
}

const FBox AToroidalMap::GetMapRange() const
{
	return BackgroundComponent->GetBackgroundBoundingBox();
}
