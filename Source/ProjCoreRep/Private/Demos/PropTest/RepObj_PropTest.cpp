#include "RepObj_PropTest.h"
#include "Util/Core/LogUtilLib.h"
#include "DemoUtils/DemoUtilLib.h"

#include "Net/UnrealNetwork.h"

URepObj_PropTest::URepObj_PropTest()
{
}

// Replicate key needs to be changed each time object needs to be replicated
int32 URepObj_PropTest::GetRepKey() const
{
	return RepKey;
}

void URepObj_PropTest::PrintMe_Implementation() 
{
	M_LOGFUNC();
	M_LOG( TEXT("Object: %s"), *ULogUtilLib::GetNameAndClassSafe(this) );
	M_LOG( TEXT("%s= \"%s\""), GET_MEMBER_NAME_STRING_CHECKED(URepObj_PropTest, RepString), *RepString );
	M_LOG( TEXT("%s= \"%s\""), GET_MEMBER_NAME_STRING_CHECKED(URepObj_PropTest, StringField), *StringField );
}

void URepObj_PropTest::UpdateProps_Implementation()
{
	M_LOGFUNC();
	RepString = UDemoUtilLib::GetUpdatedString(RepString);
	StringField = UDemoUtilLib::GetUpdatedString(StringField);
	RepKey++;
}


void URepObj_PropTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	
	DOREPLIFETIME(URepObj_PropTest, RepString);
}
