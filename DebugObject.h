// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DebugObject.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UDebugObject : public UObject
{
	GENERATED_BODY()
	
public:

	//TArray< TPair< FString, FVector > > DeltaNeedsAndTheirPositions;
	//TPair< FString, FVector > DeltaMood;

	FString DebugTextToDisplay;

	//TO DO: instead be a T<Array> of Widgets with a number of event listeners
	
	//THis should be inline
	UFUNCTION()
	void OnDebugNumChanged( int32 NewDebugNum );

private:
	//FVector CurrentPositionOffset

};



