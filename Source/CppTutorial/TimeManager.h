// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MathUtil.h"
#include "GameFramework/Actor.h"
#include "TimeManager.generated.h"

UCLASS()
class CPPTUTORIAL_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();

	// Actor tick
	void Tick(float DeltaSeconds) override;

	// Helper getters
	UFUNCTION(BlueprintCallable)
	float GetTimeFactor();
	UFUNCTION(BlueprintCallable)
	bool GetAbilityAvailiable();
	UFUNCTION(BlueprintCallable)
	float GetCurrentReversableTime();

	// Time reverse control
	UFUNCTION(BlueprintCallable)
	void BeginTimeReverse();
	UFUNCTION(BlueprintCallable)
	void EndTimeReverse();

	// Enable control
	UFUNCTION(BlueprintCallable)
	void EnableTimeReverseAbility();
	UFUNCTION(BlueprintCallable)
	void DisableTimeReverseAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// This is the current active factor of time
	UPROPERTY(BlueprintReadOnly)
	float CurrentTimeFactor = 1.0f;
	UPROPERTY(BlueprintReadOnly)
	float CurrentRecordedTime = 0.0f;
	
	UPROPERTY(BlueprintReadOnly)
	bool TimeReversalAbilityEnabled = false;

public:
	// Gloable ability preset
	UPROPERTY(BlueprintReadWrite)
	float NormalTimeFactor = 1.0f;
	UPROPERTY(BlueprintReadWrite)
	float ReverseTimeFactor = -3.0f;
	UPROPERTY(BlueprintReadWrite)
	float ReverseTimeThreshold = 3.0f;
	UPROPERTY(BlueprintReadWrite)
	float ReverseTimeMaximum = 15.0f;
};
