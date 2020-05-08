#pragma once

#include "DemoUtils/DemoUtilTypes.h"
#include "RepActorTypes.generated.h"



USTRUCT(BlueprintType)
struct FRepActorTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Testing, Meta=(Bitmask, BitmaskEnum="ERepTestFlags"))
	ERepTestFlags TestFlags = ERepTestFlags::Default;

};

USTRUCT(BlueprintType)
struct FRepTimerTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Testing)
	EMyFrameworkPoint SetTimerPoint = EMyFrameworkPoint::AtBeginPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Testing|Timer|Demo")
	bool bPeriodic = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Testing|Timer|Demo")
	float TimerInterval = 3.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Testing)
	FRepActorTest Test;
};


USTRUCT(BlueprintType)
struct FRepActorTestProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Testing, Meta=(Bitmask, BitmaskEnum="ERepTestFlags"))
	FRepTimerTest TimerTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Testing, Meta=(Bitmask, BitmaskEnum="ERepTestFlags"))
	FRepActorTest BeginPlay;
};

USTRUCT(BlueprintType)
struct FRepActorProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Testing, Meta=(ShowOnlyInnerProperties=true))
	FRepActorTestProps Test;
};
