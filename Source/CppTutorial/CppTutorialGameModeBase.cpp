// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTutorialGameModeBase.h"

void ACppTutorialGameModeBase::InitGameState()
{
	Super::InitGameState();

	// Check if no hard override is active
	if (DefaultPawnClass == ADefaultPawn::StaticClass())
	{
		// Update to custom implementation
		DefaultPawnClass = CustomXPPawnClass;

	}
}