// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Create these objects here and not in constructor because we only need them on the client.
	PawnMappingContext = NewObject<UInputMappingContext>(this);

	MoveAction = NewObject<UInputAction>(this);
	MoveAction->ValueType = EInputActionValueType::Axis3D;
	PawnMappingContext->MapKey(MoveAction, EKeys::W);
}
