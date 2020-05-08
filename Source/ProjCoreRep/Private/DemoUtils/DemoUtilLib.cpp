#include "DemoUtilLib.h"
#include "GameFramework/Actor.h"
#include "Algo/Transform.h"
#include "Util/Core/LogUtilLib.h"

bool UDemoUtilLib::ShouldDoRepTest(const AActor* const TestOwner, const FRepActorTest& InTest)
{
	return ShouldDoRepTestByFlags(TestOwner, InTest.TestFlags);
}

bool UDemoUtilLib::ShouldDoRepTestByFlags(const AActor* TestOwner, ERepTestFlags const InFlags)
{
	if(nullptr == TestOwner)
	{
		M_LOG_WARN(TEXT("When calling \"%s\" Owner is nullptr!"), TEXT(__FUNCTION__));
		return false;
	}

	if(TestOwner->HasAuthority())
	{
		return (InFlags & ERepTestFlags::DoOnServer) != ERepTestFlags::None;
	}
	else
	{
		checkf( ! TestOwner->HasAuthority(), TEXT("This code must be executed inside the branch where there's no authority") );
		return (InFlags & ERepTestFlags::DoOnClient) != ERepTestFlags::None;
	}
}

ERepTestEnum UDemoUtilLib::GetUpdatedEnum(AActor* Sender)
{
	if (Sender->HasAuthority())
	{
		return ERepTestEnum::UpdatedOnServer;
	}
	else
	{
		return ERepTestEnum::UpdatedOnClient;
	}
}

FString UDemoUtilLib::GetRepTestEnumString(const ERepTestEnum InEnum)
{
	switch (InEnum)
	{
	case ERepTestEnum::Uninitialized:
		return FString(TEXT("Uninitialized"));
	case ERepTestEnum::UpdatedOnClient:
		return FString(TEXT("UpdatedOnClient"));
	case ERepTestEnum::UpdatedOnServer:
		return FString(TEXT("UpdatedOnServer"));
	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

void UDemoUtilLib::K2_LogRepTestEnum(const FString& TestEnum, const ERepTestEnum InEnum)
{
	return LogRepTestEnum(*TestEnum, InEnum);
}

void UDemoUtilLib::LogRepTestEnum(const TCHAR* const TestEnum, const ERepTestEnum InEnum)
{
	ULogUtilLib::LogStringC(TestEnum, GetRepTestEnumString(InEnum));
}

void UDemoUtilLib::UpdateStringArray(TArray<FString>& StringArray)
{
	for(FString& S : StringArray)
	{
		UpdateString(S);
	}
}
	
void UDemoUtilLib::UpdateStringSet(TSet<FString>& StringSet)
{
	const TSet<FString> OldSet = StringSet;

	StringSet.Empty();
	for(const FString& S : OldSet)
	{
		StringSet.Add(GetUpdatedString(S));
	}
}

void UDemoUtilLib::UpdateStringToIntMap(TMap<FString,int32>& StringToIntMap)
{
	const TMap<FString, int32> OldMap = StringToIntMap;

	StringToIntMap.Empty();
	for(const TPair<FString, int32>& Pair : OldMap)
	{
		StringToIntMap.Add(GetUpdatedString(Pair.Key), Pair.Value + 1);
	}
}

void UDemoUtilLib::UpdateTextArray(TArray<FText>& TextArray)
{
	for(FText& T : TextArray)
	{
		UpdateText(T);
	}
}

void UDemoUtilLib::UpdateString(FString& String)
{
	String.Append(DemoUtils::MY_UPDATED_STRING_POSTFIX);
}

void UDemoUtilLib::UpdateText(FText& String)
{
	String = GetUpdatedText(String);
}

FString UDemoUtilLib::GetUpdatedString(const FString& String)
{
	return String + DemoUtils::MY_UPDATED_STRING_POSTFIX;
}

FText UDemoUtilLib::GetUpdatedText(const FText& Text)
{
	return FText::Format(FText::FromString("{0} {1}"), Text, DemoUtils::MY_UPDATED_TEXT_POSTFIX);
}

TArray<FStringFormatArg> UDemoUtilLib::StringArrayToFormatArgs(const TArray<FString>& InArgs)
{
	TArray<FStringFormatArg> FormatArgs;
	Algo::Transform
	(
		InArgs, FormatArgs, 
		[](const FString& S) 
		{
			return FStringFormatArg(S); 
		}
	);
	return FormatArgs;
}

ENetLogFlags UDemoUtilLib::GetDefaultLogFlags()
{
	return ENetLogFlags::Default | ENetLogFlags::Owner;
}
