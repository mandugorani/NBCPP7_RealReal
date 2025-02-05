// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacterPawn.generated.h"


UCLASS()
class NBCPP7_REALREAL_API AMyCharacterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCharacterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent); // ÄÚÆÄÀÏ·µ

	//UPROPERTY(VisibleAnywhere)
	//USpringArmComponent* SpringArm;
	//UPROPERTY(VisibleAnywhere)
	//UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveForwardAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookUpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveRightAction; // 0131 test

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float TurnRate = 45.0f;

	void OnMoveForward(const FInputActionValue& Value);
	void OnTurn(const FInputActionValue& Value);
	void OnLookUp(const FInputActionValue& Value);
	void OnMoveRight(const FInputActionValue& Value); // 0131 test
};
