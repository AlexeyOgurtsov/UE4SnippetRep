#pragma once

#include "DemoUtilTypes.generated.h"

/** ERepTestFlags*/
UENUM(BlueprintType, Category = "Replication|Demo|Test")
enum class ERepTestEnum : uint8
{
	Uninitialized = 0 UMETA(DisplayName="Uninitialized"),
	UpdatedOnClient = 1 UMETA(DisplayName="Updated on client"),
	UpdatedOnServer = 2 UMETA(DisplayName="Updated on server")
};

/** ERepTestFlags*/
UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor=true), Category="Replication|Demo|Test")
enum class ERepTestFlags : uint8
{
	/** None*/
	None = 0 UMETA(DisplayName="None")

	/** DoOnServer*/
	, DoOnServer = 1 << 0 UMETA(DisplayName="Do On Server")

	/** DoOnClient*/
	, DoOnClient = 1 << 1 UMETA(DisplayName="Do On Client")

	/** 
	 * Do both on server and client.
	 * */
	, DoOnBoth = DoOnServer | DoOnClient UMETA(DisplayName="Do On Both")
	
	/** Default*/
	, Default = DoOnBoth UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ERepTestFlags);

USTRUCT(BlueprintType)
struct FRepTestFlags_UpdateObserve
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Replication|Demo|Utils", Meta=(Bitmask, BitmaskEnum="ERepTestFlags"))	
	ERepTestFlags UpdateFlags = ERepTestFlags::DoOnServer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Replication|Demo|Utils", Meta=(Bitmask, BitmaskEnum="ERepTestFlags"))	
	ERepTestFlags ObserveFlags = ERepTestFlags::DoOnClient;
};

UENUM(BlueprintType, Category="Framework|Demo|Test")
enum class EMyFrameworkPoint : uint8
{
	/** None*/
	None = 0 UMETA(DisplayName="None")

	/** Constructor*/
	, AtConstructor = 1 UMETA(DisplayName="At Constructor")

	/** PostInitProperties*/
	, AtPostInitProperties = 2 UMETA(DisplayName="At PostInitProperties")

	/** BeginPlay*/
	, AtBeginPlay = 3 UMETA(DisplayName="At BeginPlay")

	/** BeginPlay*/
	, Custom = 4 UMETA(DisplayName = "Custom")
};

namespace DemoUtils
{
	const float MY_UPDATED_FLOAT = 3.0F;
	const int32 MY_UPDATED_INT32 = 3;

	const FString MY_UPDATED_STRING_POSTFIX = TEXT("_UPDATED");
	const FText MY_UPDATED_TEXT_POSTFIX = FText::FromString(TEXT("_UPDATED"));
} // DemoUtils
