// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimepointBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CPPTUTORIAL_API UTimepointBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	float Time = 0.0f;

	/*
	*    T-   ---> T   ---> T+
	*   this      RV      other
	* 
	*    T- + distance * abs(T+ - T-)
	* 
	* Example:
	* 
	* - TIME goes FWD
	*   T-: 0.0f (this)
	*   T : 0.5f
	*	T+: 1.0f (other)
	*	d = 0.5f
	* 
	* - TIME goes BWG
	*	T-: 1.0f (this)
	*	T : 0.5f 
	*	T+: 0.0f (other)
	*	d = 0.5f
	*/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UTimepointBase* Interpolate(const UTimepointBase* other, float distance);

private:
	virtual UTimepointBase* Interpolate_Implementation(const UTimepointBase* other, float distance) const;
};
