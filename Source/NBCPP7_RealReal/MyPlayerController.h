// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyCharacterPawn.h"
#include "MyDronePawn.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NBCPP7_REALREAL_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* MappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* SwitchPawnAction;

private:
    AMyCharacterPawn* CharacterPawn;
    AMyDronePawn* DronePawn;

    void OnSwitchPawn(const FInputActionValue& Value);
};

