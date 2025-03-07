// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyFlipbookNotifierComponent.generated.h"

class UPaperFlipbookComponent;

DECLARE_MULTICAST_DELEGATE(FOnFrameNotify);

UCLASS(ClassGroup = Equipment, meta = (BlueprintSpawnableComponent))
class MYVAMPIRESURVIVORS_API UMyFlipbookNotifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMyFlipbookNotifierComponent();

public:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~End of UActorComponent interface

	void AddOnceEventListener(const FOnFrameNotify::FDelegate& Listener);

	void SetNotifyFrame(int NewNotifyFrame);
	void SetFlipbookComponent(const UPaperFlipbookComponent* NewFlipbookComponent);

private:
	FOnFrameNotify OnFrameNotify;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Flipbook, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<const UPaperFlipbookComponent> FlipbookComponent;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = Flipbook, meta = (AllowPrivateAccess = "true"))
	int NotifyFrame = 0;
};
