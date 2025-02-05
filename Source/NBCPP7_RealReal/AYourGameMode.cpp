// Fill out your copyright notice in the Description page of Project Settings.
 

#include "AYourGameMode.h"
#include "MyCharacterPawn.h"
#include "MyDronePawn.h"
#include "MyPlayerController.h"

AAYourGameMode::AAYourGameMode()
{
	DefaultPawnClass = AMyCharacterPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}