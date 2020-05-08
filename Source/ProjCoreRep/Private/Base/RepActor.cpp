#include "RepActor.h"

#include "DemoUtils\DemoUtilLib.h"
#include "Util\Core\LogUtilLib.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Net/UnrealNetwork.h"
#include "Logging/LogMacros.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

DECLARE_LOG_CATEGORY_EXTERN(RepActLog, Display, All);

ARepActor::ARepActor()
{
	bReplicates = true;
	InitMesh();
	RootComponent = SMComponent;

	SetupTestTimerIfNecessary(EMyFrameworkPoint::AtConstructor, GetTestProps().TimerTest);
}

void ARepActor::PrintMe_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

// ~Initialization Begin
void ARepActor::PostInitProperties()
{
	M_LOGFUNC();
	Super::PostInitProperties();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	// WARNING!!! It's unsafe to use property values of the CHILD here!!!! They are NOT yet initialized!!!
	// Q. Seems like it's called from server only!
}

void ARepActor::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});

	SetupTestTimerIfNecessary(EMyFrameworkPoint::AtBeginPlay, GetTestProps().TimerTest);
	DoBeginPlayTestIfNecessary();
}

void ARepActor::SetupTestTimerIfNecessary(EMyFrameworkPoint const InCallingPoint, const FRepTimerTest& InTestProps)
{
	if(ShouldDoRepTest(InTestProps.Test))
	{
		if(InCallingPoint == InTestProps.SetTimerPoint)
		{
			ThisLog
			(
			 	TEXT(__FUNCTION__),
			 	TEXT("Setting up timer; TimerInterval = {0}; bPeriodic=\"{1}\""), 
				TArray<FStringFormatArg> { 
					InTestProps.TimerInterval, 
					(InTestProps.bPeriodic ? TEXT("YES") : TEXT("no")) 
				} 
			);
			GetWorldTimerManager().SetTimer(TestTimerHandle, this, &ARepActor::DoOnTimerTestIfNecessary, InTestProps.TimerInterval, InTestProps.bPeriodic);
		}
	}
}

void ARepActor::DoOnTimerTestIfNecessary()
{
	ThisLog
	(
	 	TEXT(__FUNCTION__), 
		TEXT("Timer test: time=%f; time_since_creation=%f"), 
		{
	       		GetWorld()->GetTimeSeconds(), 
			GetGameTimeSinceCreation() 
		} 
	);
	TimerTest();
}

void ARepActor::TimerTest_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ARepActor::DoBeginPlayTestIfNecessary()
{
	DoTestIfNecessary(EMyFrameworkPoint::AtBeginPlay, GetTestProps().BeginPlay, [this]() { ARepActor::BeginPlayTest(); } );
}

void ARepActor::BeginPlayTest_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ARepActor::DoTestIfNecessary(EMyFrameworkPoint const InCallingPoint, const FRepActorTest& InTest, TFunction<void()> TestFunc)
{
	if(ShouldDoRepTest(InTest))
	{
		ThisLog(TEXT(__FUNCTION__), TEXT("Test"), {});
		TestFunc();
	}
}

bool ARepActor::ShouldDoRepTest(const FRepActorTest& InTest) const
{
	return UDemoUtilLib::ShouldDoRepTest(this, InTest);
}

void ARepActor::PostNetInit()
{
	M_LOGFUNC();
	Super::PostNetInit();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}
// ~Initialization End

// ~Property Functions Begin		
void ARepActor::PreNetReceive()
{
	Super::PreNetReceive();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ARepActor::PostNetReceive()
{
	Super::PostNetReceive();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}
// ~Property Functions End

// ~Role Begin
void ARepActor::PostNetReceiveRole()
{
	Super::PostNetReceiveRole();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}
// ~Role End

void ARepActor::OnRep_Owner()
{
	Super::OnRep_Owner();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ARepActor::OnRep_ReplicateMovement()
{	
	Super::OnRep_ReplicatedMovement();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ARepActor::OnActorChannelOpen(FInBunch& InBunch, class UNetConnection* Connection)
{
	Super::OnActorChannelOpen(InBunch, Connection);
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

// ~Replication Begin
void ARepActor::TearOff()
{
	M_LOGFUNC();
	Super::TearOff();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ARepActor::TornOff()
{
	M_LOGFUNC();
	Super::TornOff();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});

	ULogUtilLib::LogStringC(TEXT("BaseRepProp"), BaseRepProp);
}
// ~Replication End

void ARepActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARepActor, BaseRepProp);
}

void ARepActor::InitMesh()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	{
		SMComponent = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

		{
		// Assigning asset
			const FString AssetPath = TEXT("SkeletalMesh'/Game/Turret/Turret.Turret'");
			ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> SMFinder{ *AssetPath };
			if (SMFinder.Succeeded())
			{
				SMComponent->SetSkeletalMesh(SMFinder.Get(), /*bReInitPose*/true);
				// @TODO: set default animation blueprint
			}
			else
			{
				M_LOG_ERROR(TEXT("Mesh asset not found"), *AssetPath);
			}
		}
	}
}

void ARepActor::K2_ThisLog(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogStrings(*Sender, *Format, Args);
}

void ARepActor::K2_ThisLogError(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogErrorStrings(*Sender, *Format, Args);
}

void ARepActor::K2_ThisLogWarn(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogWarnStrings(*Sender, *Format, Args);
}

void ARepActor::ThisLogStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLog(Sender, Format, FormatArgs);
}

void ARepActor::ThisLogErrorStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLogError(Sender, Format, FormatArgs);
}

void ARepActor::ThisLogWarnStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLogWarn(Sender, Format, FormatArgs);
}

void ARepActor::ThisLog(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{	
	UNetUtils::NetPrefixedLog(this, Sender, Format, Args, GetDefaultLogFlags());
}

void ARepActor::ThisLogError(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{
	UNetUtils::NetPrefixedLogError(this, Sender, Format, Args, GetDefaultLogFlags());
}

void ARepActor::ThisLogWarn(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{
	UNetUtils::NetPrefixedLogWarn(this, Sender, Format, Args, GetDefaultLogFlags());
}

ENetLogFlags ARepActor::GetDefaultLogFlags() const
{
	return UDemoUtilLib::GetDefaultLogFlags();
}
