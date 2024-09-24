// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "PaperZDCharacter.h"
#include "Characters/MyVamSurCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API APlayerCharacter : public AMyVamSurCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	/**
	 * Get the width of the camera's orthographic view
	 *
	 * @return The width of the camera's orthographic view
	 */
	float GetCameraOrthoWidth() const;

	/**
	 * Get the aspect ratio of the camera
	 * 
	 * @return The aspect ratio of the camera
	 */
	float GetCameraAspectRatio() const;

	/**
	 * Get camera attached to the player character.
	 * 
	 * @return Camera attached to the player character.
	 */
	const UCameraComponent* GetFollowCamera() const;

	/**
	 * Get the view box of the camera.
	 * 
	 * @return The view box of the camera.
	 */
	const FBox GetViewBox() const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void Move(const FInputActionValue& Value);

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector2D Directionality;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_TopDownChar;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;
};
