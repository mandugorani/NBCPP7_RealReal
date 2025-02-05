// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	CharacterPawn = Cast<AMyCharacterPawn>(GetPawn());
	DronePawn = nullptr;
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EIC->BindAction(SwitchPawnAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnSwitchPawn);
	}
} // 코파일럿3 0205

void AMyPlayerController::OnSwitchPawn(const FInputActionValue& Value)
{
	APawn* CurrentPawn = GetPawn();
	if (!CurrentPawn)
	{
		return;
	}

	if (CurrentPawn->IsA(AMyCharacterPawn::StaticClass()))
	{
		if (!DronePawn)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			FVector NewSpawnLocation = CurrentPawn->GetActorLocation();
			// FVector SpawnLocation = CurrentPawn->GetActorLocation(); 에서 변경
			FRotator SpawnRotation = CurrentPawn->GetActorRotation();

			DronePawn = GetWorld()->SpawnActor<AMyDronePawn>(AMyDronePawn::StaticClass(), NewSpawnLocation, SpawnRotation, SpawnParams);
		}
		Possess(DronePawn);
	} // 캐릭터 - 드론 전환 0204
	
	else if (CurrentPawn->IsA(AMyDronePawn::StaticClass()))
	{
		if (CharacterPawn)
		{
			Possess(CharacterPawn);
		} // 드론 - 캐릭터 전환 2 0204
	}
}

