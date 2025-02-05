// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDroneGameMode.h"
#include "MyDronePawn.h"

AMyDroneGameMode::AMyDroneGameMode()
{
	DefaultPawnClass = AMyDronePawn::StaticClass();
}
