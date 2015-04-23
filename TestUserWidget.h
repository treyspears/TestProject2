// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "TestUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT2_API UTestUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "My New User Widget" )
	FString MyNewWidgetName;
	
	
};
