// Copyright Epic Games, Inc. All Rights Reserved.

#include "KrazyKatsMutiplayerGameMode.h"
#include "KrazyKatsMutiplayerPawn.h"
#include "KrazyKatsMutiplayerHud.h"

AKrazyKatsMutiplayerGameMode::AKrazyKatsMutiplayerGameMode()
{
	DefaultPawnClass = AKrazyKatsMutiplayerPawn::StaticClass();
	HUDClass = AKrazyKatsMutiplayerHud::StaticClass();
}
