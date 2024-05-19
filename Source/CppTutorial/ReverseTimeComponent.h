// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimeManager.h"
#include "TimePowerGameModeBase.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ReverseTimeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPTUTORIAL_API UReverseTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UReverseTimeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public: 
	UPROPERTY(BlueprintReadOnly)
	ATimeManager* TimeManager = nullptr;

};
