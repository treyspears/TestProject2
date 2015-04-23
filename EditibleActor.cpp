// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject2.h"
#include "EditibleActor.h"


// Sets default values
AEditibleActor::AEditibleActor()
	: TotalDamage( 200 )
	, DamageTimeInSeconds( 1.f )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEditibleActor::PostInitProperties()
{
	Super::PostInitProperties();

	ChangeDerivedProperties();
}


#if WITH_EDITOR

void AEditibleActor::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	ChangeDerivedProperties();

	Super::PostEditChangeProperty( PropertyChangedEvent );

}

#endif

// Called when the game starts or when spawned
void AEditibleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEditibleActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AEditibleActor::ChangeDerivedProperties()
{
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

