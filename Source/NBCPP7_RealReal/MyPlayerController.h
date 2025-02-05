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

    UPROPERTY(EditDefaultsOnly, Category = "Switch")
    TSubclassOf<AMyDronePawn> DronePawnClass;
    // 코파일럿 0205
    // bp_drone~ 이 아닌 코드 클래스 drone을 spawn하는 문제를 해결
    // c++클래스 drone을 스폰해서 bp_drone의 설정 반영 안되는 문제
private:
    AMyCharacterPawn* CharacterPawn;
    AMyDronePawn* DronePawn;

    void OnSwitchPawn(const FInputActionValue& Value);
};

