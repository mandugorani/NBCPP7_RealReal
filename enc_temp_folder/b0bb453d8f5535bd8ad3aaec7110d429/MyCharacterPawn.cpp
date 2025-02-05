// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterPawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "GameFramework/Actor.h"
#include "MyPlayerController.h"

// Sets default values
AMyCharacterPawn::AMyCharacterPawn()
{
	// Set root component: CapsuleComponent
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetEnableGravity(false);

	// Set up SkeletalMeshComponent
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetSimulatePhysics(false);

	// Set up SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = false; // 0131 true-> false
	SpringArmComponent->TargetArmLength = 420.0f;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritYaw =true;
	SpringArmComponent->bInheritRoll = false;

	// Set up CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false; // 스프링암한테 ~
}

// Called when the game starts or when spawned
void AMyCharacterPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<AMyPlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AMyCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMyCharacterPawn::OnMoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMyCharacterPawn::OnMoveRight);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AMyCharacterPawn::OnTurn);
		EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AMyCharacterPawn::OnLookUp);
	}
}
// Called every frame
void AMyCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CameraForward = CameraComponent->GetForwardVector();
	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + CameraForward * 100.0f, 10.0f, FColor::Red);

	FVector CameraRight = CameraComponent->GetRightVector();
	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + CameraRight * 100.0f, 10.0f, FColor::Blue);
}

// void AMyCharacterPawn::OnMoveForward(const FInputActionValue& Value)
//{
//	float ForwardValue = Value.Get<float>();
//	if (ForwardValue != 0.0f)
//	{
//		FRotator CameraYawRotation(0.0f, CameraComponent->GetComponentRotation().Yaw, 0.0f);
//		FVector Direction = FRotationMatrix(CameraYawRotation).GetUnitAxis(EAxis::X);
//
//		AddActorLocalOffset(Direction * ForwardValue * 500.0f * GetWorld()->GetDeltaSeconds(), true);
//	}
//}
void AMyCharacterPawn::OnMoveForward(const FInputActionValue& Value) {
	float ForwardValue = Value.Get<float>();
	if (ForwardValue != 0.0f) {
		FVector Direction = SpringArmComponent->GetForwardVector();
		Direction.Z = 0.0f;
		Direction.Normalize();
		AddActorWorldOffset(Direction * ForwardValue * 500.0f * GetWorld()->GetDeltaSeconds(), true);
	}
}

void AMyCharacterPawn::OnMoveRight(const FInputActionValue& Value) {
	float RightValue = Value.Get<float>();
	if (RightValue != 0.0f) {
		FVector Direction = SpringArmComponent->GetRightVector();
		Direction.Z = 0.0f;
		Direction.Normalize();
		AddActorWorldOffset(Direction * RightValue * 500.0f * GetWorld()->GetDeltaSeconds(), true);
	}
}


//void AMyCharacterPawn::OnTurn(const FInputActionValue& Value) {
//	float TurnValue = Value.Get<float>();
//	if (TurnValue != 0.0f) {
//		FRotator NewSpringArmRot = SpringArmComponent->GetRelativeRotation();
//		NewSpringArmRot.Yaw += TurnValue * TurnRate * GetWorld()->GetDeltaSeconds();
//		SpringArmComponent->SetRelativeRotation(NewSpringArmRot);
//	}
//} // 0131 test4
// 
//void AMyCharacterPawn::OnTurn(const FInputActionValue& Value)
//{
//	float TurnValue = Value.Get<float>();
//	if (TurnValue != 0.0f)
//	{
//		FRotator NewRotation = GetActorRotation();
//		NewRotation.Yaw += TurnValue * TurnRate * GetWorld()->GetDeltaSeconds();
//		SetActorRotation(NewRotation);
//		SpringArmComponent->SetWorldRotation(NewRotation);
//	} // 0204 test1
//}
void AMyCharacterPawn::OnTurn(const FInputActionValue& Value)
{
	float TurnValue = Value.Get<float>();
	if (TurnValue != 0.0f)
	{

		AddActorLocalRotation(FRotator(0.0f, TurnValue * TurnRate * GetWorld()->GetDeltaSeconds(), 0.0f));
	}
} // 0204 test2


 //위에거 적용해도 아래거 적용해도 카메라가 Turn 안됨?

void AMyCharacterPawn::OnLookUp(const FInputActionValue& Value) {
	float LookUpValue = Value.Get<float>();
	if (LookUpValue != 0.0f) {
		FRotator NewSpringArmRot = SpringArmComponent->GetRelativeRotation();
		NewSpringArmRot.Pitch = FMath::Clamp(
			NewSpringArmRot.Pitch + (-LookUpValue * 45.0f * GetWorld()->GetDeltaSeconds()),
			-70.0f,
			70.0f
		);
		SpringArmComponent->SetRelativeRotation(NewSpringArmRot);
	}
} // 0131 test4