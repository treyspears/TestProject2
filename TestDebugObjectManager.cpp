// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject2.h"
#include "TestDebugObjectManager.h"
#include "TestActor.h"
#include "DebugObject.h"
//#include "TestDebugTextObject.h"


// Sets default values
ATestDebugObjectManager::ATestDebugObjectManager()
	: TargetToAttachTo( nullptr )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectionSphere = CreateDefaultSubobject< USphereComponent >( "DetectionSphere" );

	if ( DetectionSphere )
	{
		RootComponent = DetectionSphere;
		DetectionSphere->bGenerateOverlapEvents = true;
		DetectionSphere->OnComponentBeginOverlap.AddDynamic( this, &ATestDebugObjectManager::OnBeginOverlap );
		DetectionSphere->OnComponentEndOverlap.AddDynamic( this, &ATestDebugObjectManager::OnEndOverlap );
		//DetectionSphere->OnComponentEndOverlap.RemoveDynamic( this, &ATestDebugObjectManager::OnEndOverlap );
	}
}


ATestDebugObjectManager::~ATestDebugObjectManager()
{
	//for ( TPair< ATestActor*, TestDebugTextObject* > debugObjIter : DebugObjectRegistry )
	//{
	//	delete debugObjIter.Value;

	//	debugObjIter.Value = nullptr;
	//}

	//for ( TPair< ATestActor*, UDebugObject* > debugObjIter : DebugObjectRegistry )
	//{
	//	if ( !debugObjIter.Value )
	//	{
	//		debugObjIter.Value->BeginDestroy();
	//		debugObjIter.Value = nullptr;
	//	}
	//}

	DebugObjectRegistry.Empty();
}


// Called when the game starts or when spawned
void ATestDebugObjectManager::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* theWorld = GetWorld();
	TargetToAttachTo = ATestDebugObjectManager::GetLocalPlayerPawn( theWorld );
}


// Called every frame
void ATestDebugObjectManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if( TargetToAttachTo )
	{
		FVector targetLocation = TargetToAttachTo->GetActorLocation();

		SetActorLocation( targetLocation );
	}
	else
	{
		const UWorld* theWorld = GetWorld();
		TargetToAttachTo = ATestDebugObjectManager::GetLocalPlayerPawn( theWorld );
	}

}


void ATestDebugObjectManager::OnBeginOverlap( class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
											  , bool FromSweep, const FHitResult& SweepResult )
{
	ATestActor* otherActorAsTestActor = Cast< ATestActor >( OtherActor ); 

	if( otherActorAsTestActor )
	{
		UDebugObject** findResult = nullptr;
		//TestDebugTextObject** findResult = nullptr;

		findResult = DebugObjectRegistry.Find( otherActorAsTestActor );

		if ( !findResult )
		{
			
			UDebugObject* newDebugTestObject = nullptr;
			//TestDebugTextObject* newDebugTestObject = nullptr;
			
			if ( UnusedDebugTextObjects.Num() != 0 )
			{
				newDebugTestObject = UnusedDebugTextObjects.Pop();
			}
			else
			{
				newDebugTestObject = ConstructObject< UDebugObject >( UDebugObject::StaticClass() );
				//newDebugTestObject = new TestDebugTextObject();
			}
			
			newDebugTestObject->DebugTextToDisplay = FString::FromInt( otherActorAsTestActor->DecreasingTestNum );
			DebugObjectRegistry.Add( otherActorAsTestActor, newDebugTestObject );

			otherActorAsTestActor->OnDebugNumChanged.AddDynamic( newDebugTestObject, &UDebugObject::OnDebugNumChanged );
			//otherActorAsTestActor->OnDebugNumChanged.AddDynamic( newDebugTestObject, &TestDebugTextObject::OnDebugNumChanged );
		}
	}
	
}


void ATestDebugObjectManager::OnEndOverlap( class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	ATestActor* otherActorAsTestActor = Cast< ATestActor >( OtherActor );

	if ( otherActorAsTestActor )
	{
		UDebugObject* oldDebugTestObject = nullptr;
		//TestDebugTextObject* oldDebugTestObject = nullptr;
		DebugObjectRegistry.RemoveAndCopyValue( otherActorAsTestActor, oldDebugTestObject );

		if ( oldDebugTestObject )
		{
			otherActorAsTestActor->OnDebugNumChanged.RemoveDynamic( oldDebugTestObject, &UDebugObject::OnDebugNumChanged );
			UnusedDebugTextObjects.Add( oldDebugTestObject );
		}	
	}
}


void ATestDebugObjectManager::SetDetectionSphereRadius( float newRadius )
{
	DetectionSphere->SetSphereRadius( newRadius );
}


APawn* ATestDebugObjectManager::GetLocalPlayerPawn( const UWorld* theWorld )
{
	APlayerController* localPlayerController = theWorld->GetFirstPlayerController();
	APawn* localPlayerPawn = nullptr;

	if ( localPlayerController )
	{
		localPlayerPawn = localPlayerController->GetPawn();
	}

	return localPlayerPawn;
}
