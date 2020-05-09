#pragma once

#include "Util/Net/NetUtils.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Base/RepActorTypes.h"
#include "DemoUtilTypes.h"

#include "UObject/TextProperty.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"

#include "DemoUtilLib.generated.h"

UCLASS(BlueprintType)
class UDemoUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ~Actor Test Begin
	UFUNCTION(BlueprintPure, Category = "Demo|Utils")
	static bool ShouldDoRepTest(const AActor* TestOwner, const FRepActorTest& InTest);

	UFUNCTION(BlueprintPure, Category = "Demo|Utils")
	static bool ShouldDoRepTestByFlags(const AActor* TestOwner, ERepTestFlags InFlags);
	
	static void SetupTestTimerIfNecessary
	(
		AActor* TestOwner,
		FTimerHandle& OutTimerHandle,
		EMyFrameworkPoint const InCallingPoint,
		const FRepTimerTest& InTestProps,
		const FTimerDelegate& InTimerDelegate
	);
	// ~Actor Test End

	// ~Logging Test Enum Begin
	UFUNCTION(BlueprintPure, Category = "Demo|Utils")
	static FString GetRepTestEnumString(ERepTestEnum InEnum);

	UFUNCTION(BlueprintCallable, Category = "Demo|Utils", Meta=(DisplayName="LogRepTestEnum"))
	static void K2_LogRepTestEnum(const FString& TestEnum, ERepTestEnum InEnum);

	static void LogRepTestEnum(const TCHAR* TestEnum, ERepTestEnum InEnum);
	// ~Logging Test Enum End
	
	// ~Test property update Begin
	UFUNCTION(BlueprintPure, Category = "Demo|Utils")
	static ERepTestEnum GetUpdatedEnum(AActor* Sender);

	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void UpdateStringArray(TArray<FString>& StringArray);
	
	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void UpdateStringSet(TSet<FString>& StringSet);

	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void UpdateStringToIntMap(TMap<FString,int32>& StringToIntMap);

	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void UpdateTextArray(TArray<FText>& TextArray);

	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void UpdateString(FString& String);

	UFUNCTION(BlueprintCallable, Category = "Demo|Utils")
	static void UpdateText(FText& String);

	UFUNCTION(BlueprintPure, Category = "Demo|Utils")
	static FString GetUpdatedString(const FString& String);

	UFUNCTION(BlueprintPure, Category = "Demo|Utils")
	static FText GetUpdatedText(const FText& String);
	// ~Test property update End
	
	// ~Logging Utils Begin	
	static TArray<FStringFormatArg> StringArrayToFormatArgs(const TArray<FString>& InArgs);
	// ~Logging Utils End
	
	// ~Logging utils Begin
	UFUNCTION(BlueprintPure, Category="Demo|Net")
	static ENetLogFlags GetDefaultLogFlags();
	// ~Logging utils End
};
