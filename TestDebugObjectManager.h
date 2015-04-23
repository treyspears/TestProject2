// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TestDebugObjectManager.generated.h"

class UDebugObject;
//class TestDebugTextObject;
class ATestActor;

UCLASS()
class TESTPROJECT2_API ATestDebugObjectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestDebugObjectManager();
	~ATestDebugObjectManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnBeginOverlap( class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
						, bool FromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnEndOverlap( class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

	UFUNCTION()
	void SetDetectionSphereRadius( float newRadius );

	static APawn* GetLocalPlayerPawn( const UWorld* theWorld );

	inline const TMap< ATestActor*, UDebugObject* >& GetDebugObjects() const;
	//inline const TMap< ATestActor*, TestDebugTextObject* >& GetDebugObjects() const;

	UPROPERTY( VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision" )
	USphereComponent* DetectionSphere;

private:

	TMap< ATestActor*, UDebugObject* > DebugObjectRegistry;
	//TMap< ATestActor*, TestDebugTextObject* > DebugObjectRegistry;

	TArray< UDebugObject* > UnusedDebugTextObjects;
	//TArray< TestDebugTextObject* > UnusedDebugTextObjects;

	UPROPERTY()
	APawn* TargetToAttachTo;
};


inline const TMap< ATestActor*, UDebugObject* >& ATestDebugObjectManager::GetDebugObjects() const
{
	return DebugObjectRegistry;
}

//inline const TMap< ATestActor*, TestDebugTextObject* >& ATestDebugObjectManager::GetDebugObjects() const
//{
//	return DebugObjectRegistry;
//}