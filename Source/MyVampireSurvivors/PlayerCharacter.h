// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API APlayerCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	FVector2D Directionality;

private:
	void Move(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_TopDownChar;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;
};
