#include "RepComp_PropTest.h"
#include "Util/Core/LogUtilLib.h"
#include "DemoUtils/DemoUtilLib.h"

#include "Net/UnrealNetwork.h"

URepComp_PropTest::URepComp_PropTest()
{
}

void URepComp_PropTest::BeginPlay()
{
	Super::BeginPlay();
}

void URepComp_PropTest::PrintMe_Implementation()
{
	M_LOGFUNC();
	M_LOG( TEXT("Object: %s"), *ULogUtilLib::GetNameAndClassSafe(this) );
	UNetUtils::NetPrefixedLog(this, GET_MEMBER_NAME_STRING_CHECKED(URepComp_PropTest, RepString), TEXT("{0}"), { RepString });
	UNetUtils::NetPrefixedLog(this, GET_MEMBER_NAME_STRING_CHECKED(URepComp_PropTest, StringField), TEXT("{0}"), { StringField });
}

void URepComp_PropTest::UpdateProps_Implementation()
{
	M_LOGFUNC();
	RepString = UDemoUtilLib::GetUpdatedString(RepString);
	StringField = UDemoUtilLib::GetUpdatedString(StringField);
}

void URepComp_PropTest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(URepComp_PropTest, RepString);
}
