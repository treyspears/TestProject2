// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject2.h"
#include "TestProject2GameMode.h"
#include "TestHUD.h"


ATestProject2GameMode::ATestProject2GameMode( const FObjectInitializer& objectInitializer )
	: Super( objectInitializer )
	, DebugObjectManager( nullptr )
	, DetectionSphereRadius( 2048.f )
{
	HUDClass = ATestHUD::StaticClass();


}

void ATestProject2GameMode::BeginPlay()
{
	Super::BeginPlay();

	ATestDebugObjectManager* spawnResult = GetWorld()->SpawnActor< ATestDebugObjectManager >();

	if ( spawnResult )
	{
		DebugObjectManager = spawnResult;
		DebugObjectManager->SetDetectionSphereRadius( DetectionSphereRadius );
	}
}

