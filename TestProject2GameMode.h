// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "TestDebugObjectManager.h"
#include "TestProject2GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API ATestProject2GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ATestProject2GameMode( const FObjectInitializer& objectInitializer );

	virtual void BeginPlay() override;

	float DetectionSphereRadius;

	inline const ATestDebugObjectManager* GetDebugObjectManager() const;
	
private:

	UPROPERTY()
	ATestDebugObjectManager* DebugObjectManager;
};


inline const ATestDebugObjectManager* ATestProject2GameMode::GetDebugObjectManager() const
{
	return DebugObjectManager;
}