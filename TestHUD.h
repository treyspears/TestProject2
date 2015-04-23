// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TestHUD.generated.h"

class ATestDebugObjectManager;

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API ATestHUD : public AHUD
{
	GENERATED_BODY()
	
	ATestHUD( const FObjectInitializer& objectInitializer );

	virtual void DrawHUD() override;

	void PrintDebugTextAtAllTestActorLocations();

	UPROPERTY()
	UFont* TestFont;
};
