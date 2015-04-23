// Fill out your copyright notice in the Description page of Project Settings.

#include "TestProject2.h"
#include "DebugObject.h"

void UDebugObject::OnDebugNumChanged( int32 NewDebugNum )
{
	DebugTextToDisplay = FString::FromInt( NewDebugNum );
}