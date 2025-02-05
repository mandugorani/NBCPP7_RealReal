// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MyDronePawn.generated.h"

UCLASS()
class NBCPP7_REALREAL_API AMyDronePawn : public APawn
{
	GENERATED_BODY()

public:
	AMyDronePawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveUpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookUpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* RollAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* CameraTurnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* CameraLookUpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DroneMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;

private:

	UPROPERTY(VisibleAnywhere, Category = "State")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, Category = "State")
	float FallSpeed;

	UPROPERTY(VisibleAnywhere, Category = "State")
	FRotator DroneRotation;

	UPROPERTY(VisibleAnywhere, Category = "State")
	float TiltAngle;

	float LastUpInput;

	UPROPERTY(EditAnywhere)
	float Acceleration = 1000.0f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 300.0f;

	UPROPERTY(EditAnywhere)
	float Gravity = -980.0f;

	void CalculateTilt();
	void ApplyGravity(float DeltaTime);

	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void MoveUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Roll(const FInputActionValue& Value);
	void CameraTurn(const FInputActionValue& Value);
	void CameraLookUp(const FInputActionValue& Value);
	bool IsGrounded();
};

