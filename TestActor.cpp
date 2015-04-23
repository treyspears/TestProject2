// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject2.h"
#include "TestActor.h"


// Sets default values
ATestActor::ATestActor()
	: DecreasingTestNum( 0 )
	, ElapsedTime( 0.f )
	, Speed( 100.f )
	, VelocityDirection( 1.f, 0.f, 0.f )
	, OscillatingMaterialValue( 0.f )
	, OscillatingMaterialInstance( nullptr )
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupPrimitives();
}

void ATestActor::SetupPrimitives()
{
	BaseCollisionComponent = CreateDefaultSubobject< USphereComponent >( "BaseSphereComponent" );
	TestActorMesh = CreateDefaultSubobject< UStaticMeshComponent >( "TestActorStaticMeshComponent" );

	RootComponent = BaseCollisionComponent;
	BaseCollisionComponent->bGenerateOverlapEvents = true;

	UStaticMesh* coneStaticMesh = nullptr;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshObj( TEXT( "StaticMesh'/Engine/BasicShapes/Sphere.Sphere'" ) );
	if ( staticMeshObj.Succeeded() )
	{
		coneStaticMesh = staticMeshObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> materialObj( TEXT( "Material'/Game/StarterContent/Materials/BasicShapeMaterialParameterized.BasicShapeMaterialParameterized'" ) );
	if ( materialObj.Succeeded() )
	{
		UMaterialInterface* materialInterface = materialObj.Object;

		OscillatingMaterialInstance = TestActorMesh->CreateAndSetMaterialInstanceDynamicFromMaterial( 0, materialInterface );
	}

	TestActorMesh->SetStaticMesh( coneStaticMesh );
	TestActorMesh->AttachTo( BaseCollisionComponent );
	//TestActorMesh->SetSimulatePhysics( false );
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	ChangeDerivedProperties();

}

void ATestActor::PostInitProperties()
{
	Super::PostInitProperties();

	ChangeDerivedProperties();
}


#if WITH_EDITOR

void ATestActor::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	ChangeDerivedProperties();

	Super::PostEditChangeProperty( PropertyChangedEvent );

}

#endif

// Called every frame
void ATestActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation();

	/*float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	RunningTime += DeltaTime;

	SetActorLocation(NewLocation);
	*/

	NewLocation += VelocityDirection * ( Speed * DeltaTime );

	SetActorLocation( NewLocation );

	/*
	UFont* Font = GEngine->GetSmallFont();
	FText  inText = NSLOCTEXT("IceTr3ySpears", "SomeKey", "Hello World");
	FVector2D textLocation = FVector2D(NewLocation.X, NewLocation.Y);

	FCanvasTextItem textItem(textLocation, inText, Font, FLinearColor(1.f, 0.f, 0.f, 1.f));

	*/

	/*
	const FColor boxColor(255, 0, 0);

	const UWorld* world = GetWorld();

	DrawDebugSolidBox(world, NewLocation, FVector(20.f, 20.f, 20.f), boxColor, false, -1.f, 2);
	*/

	static float  lapTime = 0.f;
	static float  lapTime2 = 0.f;

	if ( lapTime >= 1.f && DecreasingTestNum > 0 )
	{
		SetDecreasingTestNum( DecreasingTestNum - 1 );
		lapTime = 0.f;
	}

	if ( lapTime2 >= 1.25f )
	{
		SetDebugFlag( !DebugFlag );
		lapTime2 = 0.f;
	}

	lapTime += DeltaTime;
	lapTime2 += DeltaTime;


	OscillatingMaterialValue = 0.5f + ( 0.5f * FMath::Sin( 2.f * ElapsedTime ) );

	if ( OscillatingMaterialInstance )
	{
		OscillatingMaterialInstance->SetScalarParameterValue( "OscillatingValue", OscillatingMaterialValue );
	}

	ElapsedTime += DeltaTime;
}


//-----------------------------------------------------------------------------------------------
void ATestActor::ChangeDerivedProperties()
{
	/*if (!velocityDirection.IsNormalized())
	{
		velocityDirection.Normalize();
	}*/
}


int32 ATestActor::GetDecreasingTestNum() const
{
	return DecreasingTestNum;
}


void ATestActor::SetDecreasingTestNum( int32 newNum )
{
	DecreasingTestNum = newNum;

	OnDebugNumChanged.Broadcast( DecreasingTestNum );
	//Broadcast event
}


bool ATestActor::GetDebugFlag() const
{
	return DebugFlag;
}


void ATestActor::SetDebugFlag( bool newFlag )
{
	DebugFlag = newFlag;

	//Broadcast event
}