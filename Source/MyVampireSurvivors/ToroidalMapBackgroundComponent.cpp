// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMapBackgroundComponent.h"
#include "GameFramework/WorldSettings.h"
#include "FileHelpers.h"
#include "PaperTileLayer.h"
#include "PlayerCharacter.h"

UToroidalMapBackgroundComponent::UToroidalMapBackgroundComponent()
{		
	// Set the background to static
	SetMobility(EComponentMobility::Static);

	BackgroundTileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("BackgroundTileMapComponent"));
	BackgroundMarginTileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("BackgroundMarginTileMapComponent"));
}

void UToroidalMapBackgroundComponent::OnRegister()
{
	Super::OnRegister();

	BackgroundTileMapComponent->SetupAttachment(this);
	BackgroundMarginTileMapComponent->SetupAttachment(this);

	UpdateBackgroundTileMapComponent();
	UpdateBackgroundMarginTileMapComponent();
}

void UToroidalMapBackgroundComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UToroidalMapBackgroundComponent, BackgroundTileMap))
	{
		UpdateBackgroundTileMapComponent();
	}
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UToroidalMapBackgroundComponent, BackgroundMarginTileMap))
	{
		UpdateBackgroundMarginTileMapComponent();
	}
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UToroidalMapBackgroundComponent, MarginLength))
	{
		UpdateBackgroundMarginTileMapComponent();
	}
}

void UToroidalMapBackgroundComponent::UpdateBackgroundTileMapComponent()
{
	BackgroundTileMapComponent->SetTileMap(BackgroundTileMap);
}

void UToroidalMapBackgroundComponent::UpdateBackgroundMarginTileMapComponent()
{
	BackgroundMarginTileMapComponent->SetTileMap(BackgroundMarginTileMap);
	if (BackgroundTileMapComponent->TileMap && BackgroundMarginTileMapComponent->TileMap)
	{
		SetBackgroundMarginTileMapFormat();
		FillMarginTilesFromOriginal();
		PostBackgroundMarginTileMapChanged();

		MoveBackgroundMarginTileMapComponent();
	}
}

// Called when the game starts
void UToroidalMapBackgroundComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UToroidalMapBackgroundComponent::InitializeBackgroundMarginTileMapComponent()
{
	CreateBackgroundMarginTileMapAndAttach();
	SetBackgroundMarginTileMapFormat();
	FillMarginTilesFromOriginal();
	MoveBackgroundMarginTileMapComponent();

	BackgroundMarginTileMapComponent->MarkRenderStateDirty();
	BackgroundMarginTileMapComponent->RecreatePhysicsState();
	BackgroundMarginTileMapComponent->UpdateBounds();
}

void UToroidalMapBackgroundComponent::CreateBackgroundMarginTileMapAndAttach()
{
	check(BackgroundMarginTileMapComponent);
	BackgroundMarginTileMapComponent->CreateNewTileMap();
}

void UToroidalMapBackgroundComponent::SetBackgroundMarginTileMapFormat()
{
	check(BackgroundTileMapComponent->TileMap);
	check(BackgroundMarginTileMapComponent->TileMap);

	BackgroundMarginTileMapComponent->TileMap->TileWidth = BackgroundTileMapComponent->TileMap->TileWidth;
	BackgroundMarginTileMapComponent->TileMap->TileHeight = BackgroundTileMapComponent->TileMap->TileHeight;
	BackgroundMarginTileMapComponent->TileMap->PixelsPerUnrealUnit = BackgroundTileMapComponent->TileMap->PixelsPerUnrealUnit;

	const FIntVector2 MarginTileCount = ConvertUnrealUnitLengthToTileCount(GetMarginLengthPair(), BackgroundTileMapComponent->TileMap);
	const int MapWidth = BackgroundTileMapComponent->TileMap->MapWidth + MarginTileCount.X * 2;
	const int MapHeight = BackgroundTileMapComponent->TileMap->MapHeight + MarginTileCount.Y * 2;
	BackgroundMarginTileMapComponent->TileMap->ResizeMap(MapWidth, MapHeight);

	// Set tilemap collision
	check(BackgroundMarginTileMapComponent->TileMap->TileLayers.Num() == 1);
	BackgroundMarginTileMapComponent->TileMap->SetCollisionThickness(0.0f);
	BackgroundMarginTileMapComponent->TileMap->TileLayers[0]->SetLayerCollides(true);
}

void UToroidalMapBackgroundComponent::FillMarginTilesFromOriginal()
{
	check(BackgroundMarginTileMapComponent->TileMap);
	UPaperTileMap* TileMap = BackgroundMarginTileMapComponent->TileMap;

	// Width and Height of background tile map in tiles
	check(BackgroundMarginTileMapComponent->TileMap);
	int BackgroundWidth = BackgroundTileMapComponent->TileMap->MapWidth;
	int BackgroundHeight = BackgroundTileMapComponent->TileMap->MapHeight;

	const FIntVector2 MarginTileCount = ConvertUnrealUnitLengthToTileCount(GetMarginLengthPair(), BackgroundTileMapComponent->TileMap);

	TArray<int> DestinationStartXs = { 0, MarginTileCount.X + BackgroundWidth, 0, 0 }; // Left, Right, Top, Bottom
	TArray<int> DestinationStartYs = { MarginTileCount.Y, MarginTileCount.Y, 0, MarginTileCount.Y + BackgroundHeight };
	TArray<int> DestinationEndXs = {
		MarginTileCount.X,
		MarginTileCount.X * 2 + BackgroundWidth,
		MarginTileCount.X * 2 + BackgroundWidth,
		MarginTileCount.X * 2 + BackgroundWidth
	};
	TArray<int> DestinationEndYs = {
		MarginTileCount.Y + BackgroundHeight,
		MarginTileCount.Y + BackgroundHeight,
		MarginTileCount.Y,
		MarginTileCount.Y * 2 + BackgroundHeight
	};

	check(TileMap->TileLayers.Num() == 1);
	UPaperTileLayer* FillingLayer = TileMap->TileLayers[0];
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
				int SourceX = (x - MarginTileCount.X) % BackgroundWidth;
				SourceX = SourceX < 0 ? SourceX + BackgroundWidth : SourceX;
				int SourceY = (y - MarginTileCount.Y) % BackgroundHeight;
				SourceY = SourceY < 0 ? SourceY + BackgroundHeight : SourceY;
				FPaperTileInfo Tile = BackgroundTileMapComponent->GetTile(SourceX, SourceY, 0);

				// Set tile
				FillingLayer->SetCell(x, y, Tile);
			}
		}
	}
}

void UToroidalMapBackgroundComponent::PostBackgroundMarginTileMapChanged()
{
	BackgroundMarginTileMapComponent->MarkRenderStateDirty();
	BackgroundMarginTileMapComponent->RecreatePhysicsState();
	BackgroundMarginTileMapComponent->UpdateBounds();

	// Save the tile map asset
	UPaperTileMap* TileMap = BackgroundMarginTileMapComponent->TileMap;
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

void UToroidalMapBackgroundComponent::MoveBackgroundMarginTileMapComponent()
{
	const FVector Offset = GetBackgroundMarginTileMapComponentOffset();
	const FVector BackgroundLocation = BackgroundTileMapComponent->GetComponentLocation();
	BackgroundMarginTileMapComponent->SetWorldLocation(BackgroundLocation + Offset);
}

const FIntVector2 UToroidalMapBackgroundComponent::ConvertUnrealUnitLengthToTileCount(const FVector2D& UnrealUnitLength, UPaperTileMap* TileMap) const
{
	if (TileMap == nullptr)
	{
		return FIntVector2(0, 0);
	}

	const float TileWidth = TileMap->TileWidth;
	const float TileHeight = TileMap->TileHeight;

	const int XCount = FMath::CeilToInt(UnrealUnitLength.X * TileMap->PixelsPerUnrealUnit / TileWidth);
	const int YCount = FMath::CeilToInt(UnrealUnitLength.Y * TileMap->PixelsPerUnrealUnit / TileHeight);

	return FIntVector2(XCount, YCount);
}

const FVector2D UToroidalMapBackgroundComponent::GetMarginLengthPair() const
{
	return FVector2D(MarginLength, MarginLength);
}

const FVector UToroidalMapBackgroundComponent::GetBackgroundMarginTileMapComponentOffset() const
{
	check(BackgroundTileMapComponent->TileMap);
	const int TileWidth = BackgroundTileMapComponent->TileMap->TileWidth;
	const int TileHeight = BackgroundTileMapComponent->TileMap->TileHeight;
	const float PixelsPerUnrealUnit = BackgroundMarginTileMapComponent->TileMap->PixelsPerUnrealUnit;

	const FIntVector2 MarginTileCount = ConvertUnrealUnitLengthToTileCount(GetMarginLengthPair(), BackgroundTileMapComponent->TileMap);

	FVector BackgroundMarginTileMapOffset = FVector(-MarginTileCount.X * TileWidth, -MarginTileCount.Y * TileHeight, 0.0f) / PixelsPerUnrealUnit;
	return BackgroundMarginTileMapOffset;
}

const FBox UToroidalMapBackgroundComponent::GetBackgroundBoundingBox() const
{
	check(BackgroundMarginTileMapComponent);
	check(BackgroundTileMapComponent->TileMap);

	// Get size of the tile map
	UPaperTileMap* TileMap = BackgroundTileMapComponent->TileMap;
	if (TileMap->TileWidth != TileMap->TileHeight)
	{
		UE_LOG(LogTemp, Warning, TEXT("TileWidth and TileHeight should be the same, TileWidth: %f, TileHeight: %f"), TileMap->TileWidth, TileMap->TileHeight)
			return FBox();
	}
	FVector TileCMSize(TileMap->TileWidth / TileMap->PixelsPerUnrealUnit, TileMap->TileHeight / TileMap->PixelsPerUnrealUnit, 0.0f);

	float Width = TileMap->MapWidth * TileCMSize.X;
	float Height = TileMap->MapHeight * TileCMSize.Y;
	FVector RangeMin = BackgroundTileMapComponent->GetTileCornerPosition(0, 0, 0, true);
	FVector RangeMax = FVector(RangeMin.X + Width, RangeMin.Y + Height, RangeMin.Z);

	FBox Result = FBox(RangeMin, RangeMax);
	return Result;
}
