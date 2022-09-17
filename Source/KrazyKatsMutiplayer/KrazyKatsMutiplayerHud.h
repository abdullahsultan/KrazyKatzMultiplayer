// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "KrazyKatsMutiplayerHud.generated.h"


UCLASS(config = Game)
class AKrazyKatsMutiplayerHud : public AHUD
{
	GENERATED_BODY()

public:
	AKrazyKatsMutiplayerHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
