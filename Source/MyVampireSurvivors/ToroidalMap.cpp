// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMap.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"
#include "FileHelpers.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCharacter.h"
#include "Engine/Engine.h"

// Sets default values
AToroidalMap::AToroidalMap() : XMargin(0.0f), YMargin(0.0f), MapRange(FBox(EForceInit::ForceInitToZero))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BackgroundRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Background Root"));
	// Set the background to the XY plane
	BackgroundRoot->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	// Set the background to static
	BackgroundRoot->SetMobility(EComponentMobility::Static);
	RootComponent = BackgroundRoot;

	Background = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("Background"));
	Background->SetupAttachment(RootComponent);

	MarginTileMap = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("Margin Tile Map"));
	MarginTileMap->SetupAttachment(RootComponent);
}

#if WITH_EDITOR
void AToroidalMap::CreateMarginTileMap()
{
	if (MarginTileMap == nullptr)
	{
		return;
	}

	UPaperTileMap* TileMap = MarginTileMap->TileMap;
	if (TileMap == nullptr)
	{
		return;
	}

	// Set tile format
	const float TileWidth = Background->TileMap->TileWidth;
	const float TileHeight = Background->TileMap->TileHeight;
	const float PixelsPerUnrealUnit = Background->TileMap->PixelsPerUnrealUnit;
	TileMap->TileWidth = TileWidth;
	TileMap->TileHeight = TileHeight;
	TileMap->PixelsPerUnrealUnit = PixelsPerUnrealUnit;

	// Get number of margin tiles
	SetUpMarginFromCameraSetting();
	const float XMarginPixel = XMargin * PixelsPerUnrealUnit;
	const int XMarginTile = int(XMarginPixel / TileWidth + 1);
	const float YMarginPixel = YMargin * PixelsPerUnrealUnit;
	const int YMarginTile = int(YMarginPixel / TileHeight + 1);

	// Set location of the margin tile map
	FVector BackgroundOrigin = Background->GetComponentLocation();
	FVector MartinTileMapOffset = FVector(-XMarginTile * TileWidth, -YMarginTile * TileHeight, 0.0f) / PixelsPerUnrealUnit;
	FVector MarginOrigin = BackgroundOrigin + MartinTileMapOffset;
	MarginTileMap->SetWorldLocation(MarginOrigin);

	// Setup tile map asset
	// Set tile map size
	TileMap->MapWidth = Background->TileMap->MapWidth + XMarginTile * 2;
	TileMap->MapHeight = Background->TileMap->MapHeight + YMarginTile * 2;

	// Initialize layer of the margin tile map
	if (TileMap->TileLayers.Num() > 1)
	{
		// Clear all layers
		TileMap->TileLayers.Empty();
	}
	if (TileMap->TileLayers.Num() == 0)
	{
		// Create a new layer
		UPaperTileLayer* NewLayer = NewObject<UPaperTileLayer>(TileMap);
		if (NewLayer != nullptr)
		{
			TileMap->TileLayers.Add(NewLayer);
		}
	}

	// Fill margin tile map with the original tile map
	UPaperTileLayer* Layer = TileMap->TileLayers[0];
	TArray<int> DestinationStartXs = { 0, XMarginTile + Background->TileMap->MapWidth, 0, 0 }; // Left, Right, Top, Bottom
	TArray<int> DestinationStartYs = { YMarginTile, YMarginTile, 0, YMarginTile + Background->TileMap->MapHeight };
	TArray<int> DestinationEndXs = {
		XMarginTile,
		XMarginTile * 2 + Background->TileMap->MapWidth,
		XMarginTile * 2 + Background->TileMap->MapWidth,
		XMarginTile * 2 + Background->TileMap->MapWidth
	};
	TArray<int> DestinationEndYs = {
		YMarginTile + Background->TileMap->MapHeight,
		YMarginTile + Background->TileMap->MapHeight,
		YMarginTile,
		YMarginTile * 2 + Background->TileMap->MapHeight
	};

	for (int i = 0; i < 4; ++i)
	{
		int DestinationStartX = DestinationStartXs[i];
		int DestinationStartY = DestinationStartYs[i];
		int DestinationEndX = DestinationEndXs[i];
		int DestinationEndY = DestinationEndYs[i];
		// Copy tiles
		for (int y = DestinationStartY; y < DestinationEndY; ++y)
		{
			for (int x = DestinationStartX; x < DestinationEndX; ++x)
			{
				// Get tile
				int SourceX = (x - XMarginTile) % Background->TileMap->MapWidth;
				SourceX = SourceX < 0 ? SourceX + Background->TileMap->MapWidth : SourceX;
				int SourceY = (y - YMarginTile) % Background->TileMap->MapHeight;
				SourceY = SourceY < 0 ? SourceY + Background->TileMap->MapHeight : SourceY;
				FPaperTileInfo Tile = Background->GetTile(SourceX, SourceY, 0);

				// Set tile
				Layer->SetCell(x, y, Tile);
			}
		}
	}
	MarginTileMap->MarkRenderStateDirty();

	// Save modifyed tile map asset
	TileMap->MarkPackageDirty();
	TileMap->PostEditChange();

	FSoftObjectPath MarginTileMapPath = FSoftObjectPath(TileMap);
	FString AssetPath = MarginTileMapPath.ToString();

	FString PackagePath = FPackageName::ObjectPathToPackageName(AssetPath);
	UPackage* Package = TileMap->GetPackage();
	if (Package != nullptr)
	{
		TArray<UPackage*> PackagesToSave;
		PackagesToSave.Add(Package);
		bool bSaveSuccess = UEditorLoadingAndSavingUtils::SavePackages(PackagesToSave, true);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("save successed %b"), bSaveSuccess));
	}
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
	SetUpMarginFromCameraSetting();
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

void AToroidalMap::SetUpMarginFromCameraSetting()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}

	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings == nullptr)
	{
		return;
	}

	AGameModeBase* GameMode = WorldSettings->DefaultGameMode.GetDefaultObject();
	if (GameMode == nullptr)
	{
		return;
	}

	APawn* Pawn = GameMode->DefaultPawnClass.GetDefaultObject();
	if (Pawn == nullptr)
	{
		return;
	}

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Pawn);
	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot cast DefaultPawnClass to APlayerCharacter"))
		return;
	}

	float OrthoWidth = PlayerCharacter->GetCameraOrthoWidth();
	float Aspect = PlayerCharacter->GetCameraAspectRatio();

	XMargin = OrthoWidth / 2.0f;
	YMargin = OrthoWidth / Aspect / 2.0f;
}
