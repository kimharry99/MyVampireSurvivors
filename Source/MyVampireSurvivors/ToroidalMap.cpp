// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMap.h"
#include "PaperTileMap.h"
#include "Engine/Engine.h"

// Sets default values
AToroidalMap::AToroidalMap() : XMargin(0.0f), YMargin(0.0f), MapRange(FBox(EForceInit::ForceInitToZero))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Background = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("Background"));
	// Set the background to the XY plane
	Background->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	RootComponent = Background;
}

void AToroidalMap::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//if (Plane->GetStaticMesh() != nullptr)
	//{
	//	float Width = MapRange.Max.X - MapRange.Min.X;
	//	float Height = MapRange.Max.Y - MapRange.Min.Y;

	//	FVector PlaneExtent = Plane->GetStaticMesh()->GetBounds().BoxExtent;
	//	FVector PlaneSizeCM = PlaneExtent * 2.0f;
	//	FVector ScaleFactor = FVector((Width + XMargin * 2.0f) / PlaneSizeCM.X, (Height + YMargin * 2.0f) / PlaneSizeCM.Y, 1.0f);
	//	Plane->SetWorldScale3D(ScaleFactor);
	//}
}

#if WITH_EDITOR
void AToroidalMap::CreateMarginTileMap()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CreateMarginTileMap"));
}
#endif // WITH_EDITOR

// Called when the game starts or when spawned
void AToroidalMap::BeginPlay()
{
	Super::BeginPlay();

	if (Background == nullptr)
	{
		return;
	}

	// Get size of the tile map
	UPaperTileMap* TileMap = Background->TileMap;
	if (TileMap == nullptr)
	{
		return;
	}
	if (TileMap->TileWidth != TileMap->TileHeight)
	{
		UE_LOG(LogTemp, Warning, TEXT("TileWidth and TileHeight should be the same, TileWidth: %f, TileHeight: %f"), TileMap->TileWidth, TileMap->TileHeight)
		return;
	}
	FVector TileCMSize(TileMap->TileWidth / TileMap->PixelsPerUnrealUnit, TileMap->TileHeight / TileMap->PixelsPerUnrealUnit, 0.0f);

	// Initialize MapRange
	float Width = TileMap->MapWidth * TileCMSize.X;
	float Height = TileMap->MapHeight * TileCMSize.Y;
	FVector RangeMin = Background->GetComponentLocation() - TileCMSize * 0.5f; // Shift map range min to left top of tile map
	FVector RangeMax = FVector(RangeMin.X + Width, RangeMin.Y + Height, RangeMin.Z);
	MapRange = FBox(RangeMin, RangeMax);

	DrawDebugBox(GetWorld(), MapRange.GetCenter(), MapRange.GetExtent(), FColor::Red, true, -1, 0, 10.0f);

	float OrthoWidth = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetOrthoWidth();
	float Aspect = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraCachePOV().AspectRatio;
	XMargin = OrthoWidth / 2.0f;
	YMargin = OrthoWidth / Aspect / 2.0f;
}

void AToroidalMap::HandleMapBoundary(AActor* PlayerCharacter, FBox& ViewBox) const
{
	FVector CharacterPosition = PlayerCharacter->GetActorLocation();

	// Check the player escape the map
	if (!MapRange.IsInsideXY(CharacterPosition))
	{
		// Move the player and the objects in the view box to the opposite side of the map
		TArray<FBox> PossibleDestinations;
		GetCorrespondingRegions(PossibleDestinations, ViewBox);

		// Find the destination which has the center is in the map
		FBox Destination = FBox(EForceInit::ForceInitToZero);
		for (const FBox& Box : PossibleDestinations)
		{
			if (MapRange.IsInsideXY(Box.GetCenter()))
			{
				Destination = Box;
				break;
			}
		}

		// Wrap the view box to array
		TArray<FBox> SourceRegions;
		SourceRegions.Add(ViewBox);

		TransferObjectsFromMultiSource(SourceRegions, Destination);

		ViewBox = Destination;
		return;
	}

	// Check the view box escape the map
	if (!MapRange.IsInsideXY(ViewBox))
	{
		// Move the objects in the opposite sides of the map to the view box
		TArray<FBox> SourceRegions;
		GetCorrespondingRegions(SourceRegions, ViewBox);
		TransferObjectsFromMultiSource(SourceRegions, ViewBox);

		return;
	}
}

void AToroidalMap::GetCorrespondingRegions(TArray<FBox>& OutRegions, const FBox& Box) const
{
	OutRegions.Empty();
	if (Box.Min.X > Box.Max.X || Box.Min.Y > Box.Max.Y)
	{
		UE_LOG(LogTemp, Error, TEXT("Box.Min should be less than Box.Max, Box: %s"), *Box.ToString())
		return;
	}

	float Width = MapRange.Max.X - MapRange.Min.X;
	float Height = MapRange.Max.Y - MapRange.Min.Y;

	// Left side escape
	if (Box.Min.X < MapRange.Min.X)
	{
		OutRegions.Add(Box.ShiftBy(FVector(Width, 0.0f, 0.0f)));
	}
	// Right side escape
	if (Box.Max.X > MapRange.Max.X)
	{
		OutRegions.Add(Box.ShiftBy(FVector(-Width, 0.0f, 0.0f)));
	}
	// Top side escape
	if (Box.Min.Y < MapRange.Min.Y)
	{
		OutRegions.Add(Box.ShiftBy(FVector(0.0f, Height, 0.0f)));
	}
	// Bottom side escape
	if (Box.Max.Y > MapRange.Max.Y)
	{
		OutRegions.Add(Box.ShiftBy(FVector(0.0f, -Height, 0.0f)));
	}
	// Diagonal Left Top
	if (Box.Min.X < MapRange.Min.X && Box.Min.Y < MapRange.Min.Y)
	{
		OutRegions.Add(Box.ShiftBy(FVector(Width, Height, 0.0f)));
	}
	// Diagonal Right Top
	if (Box.Min.X < MapRange.Min.X && Box.Max.Y > MapRange.Max.Y)
	{
		OutRegions.Add(Box.ShiftBy(FVector(Width, -Height, 0.0f)));
	}
	// Diagonal Left Bottom
	if (Box.Max.X > MapRange.Max.X && Box.Min.Y < MapRange.Min.Y)
	{
		OutRegions.Add(Box.ShiftBy(FVector(-Width, Height, 0.0f)));
	}
	// Diagonal Right Bottom
	if (Box.Max.X > MapRange.Max.X && Box.Max.Y > MapRange.Max.Y)
	{
		OutRegions.Add(Box.ShiftBy(FVector(-Width, -Height, 0.0f)));
	}
}

void AToroidalMap::TransferObjectsFromMultiSource(const TArray<FBox>& SourceRegions, const FBox& Destination) const
{
	// Traverse all source regions
	for (const FBox& Source : SourceRegions)
	{
		DrawDebugBox(GetWorld(), Source.GetCenter(), Source.GetExtent(), FColor::Green, false, -1, 0, 5.0f);
		TransferObjects(Source, Destination, ECollisionChannel::ECC_GameTraceChannel2); // Use ToroidalWorld channel
	}
}

void AToroidalMap::TransferObjects(const FBox& Source, const FBox& Destination, const ECollisionChannel& QueryChannel) const
{
	// Do box trace to get all actors in source regions
	TArray<FOverlapResult> OverlapResults;

	GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Source.GetCenter(),
		FQuat::Identity,
		QueryChannel,
		FCollisionShape::MakeBox(Source.GetExtent())
	);

	if (OverlapResults.Num() == 0)
	{
		return;
	}

	// Transfer overlapped actors to destination
	const FVector Offset = Destination.GetCenter() - Source.GetCenter();
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (AActor* OverlappedActor = Result.GetActor())
		{
			FVector NewLocation = OverlappedActor->GetActorLocation() + Offset;
			OverlappedActor->SetActorLocation(NewLocation);
		}
	}
}
