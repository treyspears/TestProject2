// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class TESTPROJECT2_API TestDebugTextObject
{
public:
	TestDebugTextObject();
	~TestDebugTextObject();

	FString DebugTextToDisplay;

	//TO DO: instead be a T<Array> of Widgets with a number of event listeners

	inline void OnDebugNumChanged( int32 NewDebugNum );
};


inline void TestDebugTextObject::OnDebugNumChanged( int32 NewDebugNum )
{
	DebugTextToDisplay = FString::FromInt( NewDebugNum );
}
