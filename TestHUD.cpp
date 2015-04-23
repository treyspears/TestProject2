// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject2.h"
#include "TestHUD.h"
#include "TestActor.h"
#include "TestDebugObjectManager.h"
#include "DebugObject.h"
//#include "TestDebugTextObject.h"
#include "TestProject2GameMode.h"

ATestHUD::ATestHUD( const FObjectInitializer& objectInitializer )
	: Super( objectInitializer )
{
	static ConstructorHelpers::FObjectFinder<UFont> FontObj( TEXT( "/Engine/EngineFonts/RobotoDistanceField" ) );

	TestFont = FontObj.Object;
}

void ATestHUD::DrawHUD()
{
	Super::DrawHUD();

	PrintDebugTextAtAllTestActorLocations();
}


void ATestHUD::PrintDebugTextAtAllTestActorLocations()
{
	const float SHADOW_OFFSET = 2.f;
	const float SCALE_Z_FACTOR = 100.f;
	const FVector OFFSET_TEXT_POSITION( 35.f, 0.f, 0.f );

	const ATestProject2GameMode* theGameMode = static_cast< ATestProject2GameMode* >( GetWorld()->GetAuthGameMode() );
	const ATestDebugObjectManager* theDebugObjectManager = theGameMode->GetDebugObjectManager();
	const TMap< ATestActor*, UDebugObject* > debugObjects = theDebugObjectManager->GetDebugObjects();
	//const TMap< ATestActor*, TestDebugTextObject* > debugObjects = theDebugObjectManager->GetDebugObjects();

	float scaleFontFactor = 0.f;
	FVector worldToScreenPositionOfActor = FVector::ZeroVector;

	for ( const TPair< ATestActor*, UDebugObject* > debugObjIter : debugObjects )
	//for ( const TPair< ATestActor*, TestDebugTextObject* > debugObjIter : debugObjects )
	{
		worldToScreenPositionOfActor = Canvas->Project( debugObjIter.Key->GetActorLocation() );

		if ( worldToScreenPositionOfActor.Z <= 0.f )
			continue;

		scaleFontFactor = worldToScreenPositionOfActor.Z * SCALE_Z_FACTOR;
		worldToScreenPositionOfActor += ( OFFSET_TEXT_POSITION * scaleFontFactor );

		DrawRect( FLinearColor( 0.0843137254901961f, 0.0843137254901961f, 0.0843137254901961f, 1.f ), worldToScreenPositionOfActor.X, worldToScreenPositionOfActor.Y, 100.f * scaleFontFactor, 100.f * scaleFontFactor );
		DrawText( debugObjIter.Value->DebugTextToDisplay, FLinearColor( 0.f, 0.f, 0.f, 1.f ), worldToScreenPositionOfActor.X + SHADOW_OFFSET, worldToScreenPositionOfActor.Y + SHADOW_OFFSET, TestFont, scaleFontFactor );
		DrawText( debugObjIter.Value->DebugTextToDisplay, FLinearColor( 0.f, 1.f, 1.f, 1.f ), worldToScreenPositionOfActor.X, worldToScreenPositionOfActor.Y, TestFont, scaleFontFactor );
	}

	

	/*
	FString decreasingTestNumAsString;
	ATestActor* iterAsATestActor;
	float scaleFontFactor = 0.f;

	UWorld* theWorld = GetWorld();
	for ( TActorIterator<ATestActor> ActorIter( theWorld ); ActorIter; ++ActorIter )
	{
		worldToScreenPositionOfActor = Canvas->Project( ActorIter->GetActorLocation() );

		if( worldToScreenPositionOfActor.Z <= 0.f )
			continue;

		scaleFontFactor = worldToScreenPositionOfActor.Z * SCALE_Z_FACTOR;

		iterAsATestActor = static_cast< ATestActor* >( *ActorIter );

		decreasingTestNumAsString = FString::FromInt( iterAsATestActor->DecreasingTestNum );

		worldToScreenPositionOfActor += ( OFFSET_TEXT_POSITION * scaleFontFactor );

		DrawText( decreasingTestNumAsString, FLinearColor( 0.f, 0.f, 0.f, 1.f ), worldToScreenPositionOfActor.X + SHADOW_OFFSET, worldToScreenPositionOfActor.Y + SHADOW_OFFSET, TestFont, scaleFontFactor );
		DrawText( decreasingTestNumAsString, FLinearColor( 0.f, 1.f, 1.f, 1.f ), worldToScreenPositionOfActor.X, worldToScreenPositionOfActor.Y, TestFont, scaleFontFactor );
	}
	*/



	//DrawText( TEXT( "HELLO WORLD!" ), FVector2D( 2.f, 2.f ), TestFont, FVector2D::UnitVector, FColor::Black );
	//DrawText( TEXT( "HELLO WORLD!" ), FVector2D::ZeroVector, TestFont, FVector2D::UnitVector, FColor::Cyan );
}