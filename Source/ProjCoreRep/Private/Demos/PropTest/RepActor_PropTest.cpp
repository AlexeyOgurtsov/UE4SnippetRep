#pragma once

#include "RepActor_PropTest.h"
#include "Util\Core\LogUtilLib.h"
#include "DemoUtils\DemoUtilLib.h"

#include "Net/UnrealNetwork.h"

/**
* Struct Rep Test
* Q1. Should we add Replicated for props of the struct?
*
* Object Test
*
* Enum Test
*
* Component test
*
*
* Functions:
* 	RepNotify functions for properties?
* 
* Interface test (todo - for function calls)?
*/

ARepActor_PropTest::ARepActor_PropTest()
{
	RepTestStruct.MyStructName = TEXT("RepTestStruct");
	TestStruct.MyStructName = TEXT("TestStruct");
}

void ARepActor_PropTest::DemoUpdateProps_UsingCPPAssign()
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});


	//StringProp_Replicated_NoDoRepLifetime.Append(DemoUtils::MY_UPDATED_STRING_POSTFIX);
	//StringProp_DoRepLifetime_NoReplicated.Append(DemoUtils::MY_UPDATED_STRING_POSTFIX);

	//StringField.Append(DemoUtils::MY_UPDATED_STRING_POSTFIX);

	RepFloat = DemoUtils::MY_UPDATED_FLOAT;
	RepInt32 = DemoUtils::MY_UPDATED_INT32;
	RepStr.Append(DemoUtils::MY_UPDATED_STRING_POSTFIX);
	RepText = FText::Format(FText::FromString("{0}{1}"), RepText, DemoUtils::MY_UPDATED_TEXT_POSTFIX);
	UDemoUtilLib::UpdateStringArray(RepStrArray);
	UDemoUtilLib::UpdateStringSet(RepStrSet);
	UDemoUtilLib::UpdateStringToIntMap(RepStrIntMap);

	{
		// Enums
		RepEnum = UDemoUtilLib::GetUpdatedEnum(this);
		//RepEnumField = UDemoUtilLib::GetUpdatedEnum(this);
	}

	{
		// Structs
		RepTestStruct.TestUpdate();
		TestStruct.TestUpdate();
	}
}

void ARepActor_PropTest::BeginPlayTest_Implementation()
{
	M_LOGFUNC();
	Super::BeginPlayTest_Implementation();
	UpdateObserve_IfShould(OnBeginPlay_UpdateObserve);
}

void ARepActor_PropTest::PrintMe_Implementation()
{
	M_LOGFUNC();
	Super::PrintMe_Implementation();

	//ULogUtilLib::LogStringC(TEXT("StringField"), StringField);

	ULogUtilLib::LogFloatC(TEXT("RepFloat"), RepFloat);
	ULogUtilLib::LogInt32C(TEXT("RepInt32"), RepInt32);
	ULogUtilLib::LogStringC(TEXT("RepStr"), RepStr);
	ULogUtilLib::LogTextC(TEXT("RepText"), RepText);

	{
		// Logging enums
		UDemoUtilLib::LogRepTestEnum(TEXT("RepEnum"), RepEnum);
		//UDemoUtilLib::LogRepTestEnum(TEXT("RepEnumField"), RepEnumField);
	}

	{
		ULogUtilLib::K2LogStringArray(RepStrArray);
		ULogUtilLib::K2LogStringSet(RepStrSet);
		// @TODO
		//ULogUtilLib::LogMap(RepStrIntMap, StringDeref, IntToStringDeref);
	}

	{
		RepTestStruct.Print(this);
		TestStruct.Print(this);
	}

	// @TODO: Log new objects etc.
}

void ARepActor_PropTest::TimerTest_Implementation()
{
	Super::TimerTest_Implementation();
	UpdateObserve_IfShould(OnTimer_UpdateObserve);
}

void ARepActor_PropTest::UpdateObserve_IfShould(const FRepTestFlags_UpdateObserve& UpdateObserve)
{
	if( UDemoUtilLib::ShouldDoRepTestByFlags(this, UpdateObserve.UpdateFlags) )
	{
		DemoUpdateProps_UsingCPPAssign();
	}

	if( UDemoUtilLib::ShouldDoRepTestByFlags(this, UpdateObserve.ObserveFlags) )
	{
		PrintMe();
	}
}

void ARepActor_PropTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/**
	* Warning! It's wrong to use DOREPLIEFTIME for the given property because It's not marked as Replicated!!!
	* Causes error
	* Attempt to replicate property 'StrProperty /Script/ProjCoreRep.RepActor:StringProp_DoRepLifetime_NoReplicated' that was not tagged to replicate!
	* Please use 'Replicated' or 'ReplicatedUsing' keyword in the UPROPERTY() declaration.
	*/
	//DOREPLIFETIME(ARepActor_PropTest, StringProp_DoRepLifetime_NoReplicated);

	/**
	* Warning! If Replicated, then DOREPLIFETIME also should be USED!!!
	* Causes WARNING
	*/
	//DOREPLIFETIME(ARepActor_PropTest, StringProp_Replicated_NoDoRepLifetime);

	{
		////DOREPLIFETIME(ARepActor_PropTest, StringField);
	}
	
	{
		DOREPLIFETIME(ARepActor_PropTest, RepFloat);
		DOREPLIFETIME(ARepActor_PropTest, RepInt32);
		DOREPLIFETIME(ARepActor_PropTest, RepStr);
		DOREPLIFETIME(ARepActor_PropTest, RepText);
		DOREPLIFETIME(ARepActor_PropTest, RepStrArray);
		DOREPLIFETIME(ARepActor_PropTest, RepStrSet);
		DOREPLIFETIME(ARepActor_PropTest, RepStrIntMap);
	}

	{
		// Enums
		DOREPLIFETIME(ARepActor_PropTest, RepEnum);
		//DOREPLIFETIME(ARepActor_PropTest, RepEnumField);
	}
}

void FTestStructToReplicate::TestUpdate()
{
	RepString.Append(DemoUtils::MY_UPDATED_STRING_POSTFIX);
}

void FTestStructToReplicate::Print(ARepActor* const Owner)
{
	M_LOGFUNC();
	ULogUtilLib::LogString(TEXT("MyStructName"), MyStructName);
	ULogUtilLib::LogString(TEXT("RepString"), RepString);
}
