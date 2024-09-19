// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMapBackgroundComponent.h"
#include "GameFramework/WorldSettings.h"
#include "PaperTileLayer.h"
#include "MyVamSurGameMode.h"
#include "MyVamSurPlayerState.h"
#include "PlayerCharacter.h"

UToroidalMapBackgroundComponent::UToroidalMapBackgroundComponent()
{		
	// Set the background to static
	SetMobility(EComponentMobility::Static);

	BackgroundTileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("BackgroundTileMapComponent"));
	BackgroundMarginTileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("BackgroundMarginTileMapComponent"));
	BackgroundMarginTileMapComponent->bEditableWhenInherited = false;
}

void UToroidalMapBackgroundComponent::OnRegister()
{
	Super::OnRegister();

	BackgroundTileMapComponent->SetupAttachment(this);
	BackgroundMarginTileMapComponent->SetupAttachment(this);
}

const FBox UToroidalMapBackgroundComponent::GetBackgroundBoundingBox() const
{
	if (BackgroundTileMapComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Background tile map component is not created"))
		return FBox();
	}

	// Get size of the tile map
	UPaperTileMap* TileMap = BackgroundTileMapComponent->TileMap;
	if (TileMap == nullptr)
	{
		return FBox();
	}
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

void UToroidalMapBackgroundComponent::SetBackgroundTileMap(UPaperTileMap* BackgroundTileMap)
{
	if (BackgroundTileMap == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Background tile map is not set"))
		return;
	}

	BackgroundTileMapComponent->SetTileMap(BackgroundTileMap);
}

// Called when the game starts
void UToroidalMapBackgroundComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeBackgroundMarginTileMapComponent();
}

void UToroidalMapBackgroundComponent::InitializeBackgroundMarginTileMapComponent()
{
	CreateBackgroundMarginTileMapAndAttach();
	SetBackgroundMarginTileMapFormat();
	FillMarginTilesFromOriginal();
	MoveBackgroundMarginTileMapComponent();
}

void UToroidalMapBackgroundComponent::CreateBackgroundMarginTileMapAndAttach()
{
	if (BackgroundMarginTileMapComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Background margin tile map component is not created"))
		return;
	}

	BackgroundMarginTileMapComponent->CreateNewTileMap();
}

void UToroidalMapBackgroundComponent::SetBackgroundMarginTileMapFormat()
{
	BackgroundMarginTileMapComponent->TileMap->TileWidth = BackgroundTileMapComponent->TileMap->TileWidth;
	BackgroundMarginTileMapComponent->TileMap->TileHeight = BackgroundTileMapComponent->TileMap->TileHeight;
	BackgroundMarginTileMapComponent->TileMap->PixelsPerUnrealUnit = BackgroundTileMapComponent->TileMap->PixelsPerUnrealUnit;

	const FIntVector2 MarginTileCount = ConvertUnrealUnitLengthToTileCount(GetMarginLengthFromMainCamera(), BackgroundTileMapComponent->TileMap);
	const int MapWidth = BackgroundTileMapComponent->TileMap->MapWidth + MarginTileCount.X * 2;
	const int MapHeight = BackgroundTileMapComponent->TileMap->MapHeight + MarginTileCount.Y * 2;
	BackgroundMarginTileMapComponent->TileMap->ResizeMap(MapWidth, MapHeight);

	// Set tilemap collision
	BackgroundMarginTileMapComponent->TileMap->SetCollisionThickness(0.0f);
	BackgroundMarginTileMapComponent->TileMap->TileLayers[0]->SetLayerCollides(true);
}

void UToroidalMapBackgroundComponent::FillMarginTilesFromOriginal()
{
	UPaperTileMap* TileMap = BackgroundMarginTileMapComponent->TileMap;
	if (TileMap->TileLayers.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Background margin tile map must have only one layer"))
		return;
	}

	// Width and Height of background tile map in tiles
	int BackgroundWidth = BackgroundTileMapComponent->TileMap->MapWidth;
	int BackgroundHeight = BackgroundTileMapComponent->TileMap->MapHeight;

	const FIntVector2 MarginTileCount = ConvertUnrealUnitLengthToTileCount(GetMarginLengthFromMainCamera(), BackgroundTileMapComponent->TileMap);

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

	BackgroundMarginTileMapComponent->MarkRenderStateDirty();
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

const FVector2D UToroidalMapBackgroundComponent::GetMarginLengthFromMainCamera() const
{
	const UCameraComponent* CameraComponent = GetCharacterFollowingCamera();
	if (CameraComponent == nullptr)
	{
		const float TEMP_MARGIN = 2048.0f;
		return FVector2D(TEMP_MARGIN, TEMP_MARGIN);
	}

	return GetMarginLengthFromCameraParameter(CameraComponent->OrthoWidth, CameraComponent->AspectRatio);
}

const UCameraComponent* UToroidalMapBackgroundComponent::GetCharacterFollowingCamera() const
{
	const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr)
	{
		return nullptr;
	}

	const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PlayerController->GetPawn());
	if (PlayerCharacter == nullptr)
	{
		return nullptr;
	}

	return PlayerCharacter->GetFollowCamera();
}

const FVector2D UToroidalMapBackgroundComponent::GetMarginLengthFromCameraParameter(const float OrthogonalWidth, const float AspectRatio) const
{
	const float XMargin = OrthogonalWidth / 2.0f;
	const float YMargin = OrthogonalWidth / AspectRatio / 2.0f;

	return FVector2D(XMargin, YMargin);
}

const FVector UToroidalMapBackgroundComponent::GetBackgroundMarginTileMapComponentOffset() const
{
	const int TileWidth = BackgroundTileMapComponent->TileMap->TileWidth;
	const int TileHeight = BackgroundTileMapComponent->TileMap->TileHeight;
	const float PixelsPerUnrealUnit = BackgroundMarginTileMapComponent->TileMap->PixelsPerUnrealUnit;

	const FIntVector2 MarginTileCount = ConvertUnrealUnitLengthToTileCount(GetMarginLengthFromMainCamera(), BackgroundTileMapComponent->TileMap);

	FVector BackgroundMarginTileMapOffset = FVector(-MarginTileCount.X * TileWidth, -MarginTileCount.Y * TileHeight, 0.0f) / PixelsPerUnrealUnit;
	return BackgroundMarginTileMapOffset;
}
