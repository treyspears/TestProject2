// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

//Delegate Signatures
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDebugNumChangedSignature, int32, NewDebugNumValue );

UCLASS()
class TESTPROJECT2_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;

	UFUNCTION( BlueprintCallable, Category = "Movement" )
	void ChangeDerivedProperties();

	int32 GetDecreasingTestNum() const;
	void  SetDecreasingTestNum( int32 newNum );
	bool  GetDebugFlag() const;
	void  SetDebugFlag( bool newFlag );

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Debug" )
	int32 DecreasingTestNum;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Debug" )
	bool DebugFlag;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Movement" )
	float Speed;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Movement" )
	FVector VelocityDirection;

	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision" )
	USphereComponent* BaseCollisionComponent;

	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = "Appearance" )
	UStaticMeshComponent* TestActorMesh;

	//Delegates
	FDebugNumChangedSignature OnDebugNumChanged;

private:

	float ElapsedTime;
	float OscillatingMaterialValue;

	UPROPERTY()
	UMaterialInstanceDynamic* OscillatingMaterialInstance;

	void SetupPrimitives();
};
