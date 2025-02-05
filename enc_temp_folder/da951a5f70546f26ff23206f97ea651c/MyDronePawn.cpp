// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDronePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMyDronePawn::AMyDronePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	Velocity = FVector::ZeroVector;
	FallSpeed = 0.0f;
	TiltAngle = 0.0f;
	DroneRotation = FRotator::ZeroRotator;
}

// Called when the game starts or when spawned
void AMyDronePawn::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void AMyDronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyGravity(DeltaTime);
	CalculateTilt();

	FVector Forward = DroneRotation.Vector();
	FRotator TempRot = DroneRotation;
	FVector Right = FRotationMatrix(TempRot).GetScaledAxis(EAxis::Y);


	FVector Movement = Forward * Velocity.X + Right * Velocity.Y + FVector(0.0f, 0.0f, Velocity.Z);
	
	AddActorWorldOffset(Movement * DeltaTime, true);

}


void AMyDronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APawn::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMyDronePawn::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMyDronePawn::MoveRight);
		EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &AMyDronePawn::MoveUp);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AMyDronePawn::Turn);
		EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AMyDronePawn::LookUp);
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &AMyDronePawn::Roll);
	}
}

void AMyDronePawn::MoveForward(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	float SpeedMultiplier;

	if (GetActorLocation().Z > 0.0f) {
		SpeedMultiplier = 0.5f;
	}else{
		SpeedMultiplier = 1.0f;
	}

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	Velocity.X += Input * Acceleration * SpeedMultiplier * DeltaTime;
	Velocity.X = FMath::Clamp(Velocity.X, -MaxSpeed, MaxSpeed);
}

void AMyDronePawn::MoveRight(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	float SpeedMultiplier;

	if (GetActorLocation().Z > 0.0f) {
		SpeedMultiplier = 0.5f;
	}else{
		SpeedMultiplier = 1.0f;
	}

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	Velocity.Y += Input * Acceleration * SpeedMultiplier * DeltaTime;
	Velocity.Y = FMath::Clamp(Velocity.Y, -MaxSpeed, MaxSpeed);
}

void AMyDronePawn::MoveUp(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	Velocity.Z += Input * Acceleration * DeltaTime;
	Velocity.Z = FMath::Clamp(Velocity.Z, -MaxSpeed, MaxSpeed);
}

void AMyDronePawn::Turn(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	DroneRotation.Yaw += Input;
}

void AMyDronePawn::LookUp(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	DroneRotation.Pitch += Input;
}

void AMyDronePawn::Roll(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();
	TiltAngle += Input * 5.0f;
}

void AMyDronePawn::CalculateTilt()
{
	float RollAmount = FMath::Clamp(TiltAngle, -45.0f, 45.0f);
	DroneRotation.Roll = RollAmount;
}

void AMyDronePawn::ApplyGravity(float DeltaTime)
{
	if (GetActorLocation().Z > 0.0f)
	{
		FallSpeed += Gravity * DeltaTime;
	}
	else
	{
		FallSpeed = 0.0f;
	}
	Velocity.Z += FallSpeed * DeltaTime;
}