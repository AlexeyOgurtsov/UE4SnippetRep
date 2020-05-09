#include "PC.h"
#include "MyPawn.h"
#include "Util\Core\LogUtilLib.h"
#include "Util\Net\NetUtils.h"
#include "DemoUtils\DemoUtilLib.h"

#include "Components\InputComponent.h"

APC::APC()
{
}

// ~AActor begin
void APC::PostInitProperties()
{
	M_LOGFUNC();
	Super::PostInitProperties();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void APC::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();	

	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	UNetUtils::LogNetVars(this);

	SetTestTimer(EMyFrameworkPoint::AtBeginPlay);

	bBeginPlayCalled = true;
}

void APC::OnPawnBeginPlay_Implementation()
{
	M_LOGFUNC();
}

void APC::SetupInputComponent()
{
	M_LOGFUNC();
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("DebugOne"), IE_Pressed, this, &APC::DebugOne);
	InputComponent->BindAction(TEXT("DebugTwo"), IE_Pressed, this, &APC::DebugTwo);
	InputComponent->BindAction(TEXT("DebugThree"), IE_Pressed, this, &APC::DebugThree);
}
// ~AActor end

// ~Possession begin
void APC::OnPossess(APawn* InPawn)
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	Super::OnPossess(InPawn);
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void APC::OnUnPossess()
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	Super::OnUnPossess();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void APC::SetPawn(APawn* const InPawn)
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	Super::SetPawn(InPawn);
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}
// ~Possession end

// ~Pawn Begin
AMyPawn* APC::GetMyPawn() const
{
	return CastToMyPawn(GetPawn());
}

AMyPawn* APC::GetMyPawnChecked() const
{
	AMyPawn* const P = GetMyPawn();
	checkf(P, TEXT("Pawn must be valid instance of \"%s\""), *AMyPawn::StaticClass()->GetName());
	return P;
}

AMyPawn* APC::K2_CastToMyPawn(APawn* const InPawn) const
{
	return CastToMyPawn(InPawn);
}

AMyPawn* APC::CastToMyPawn(APawn* const InPawn) const
{
	return Cast<AMyPawn>(InPawn);
}

const AMyPawn* APC::CastToMyPawn(const APawn* const InPawn) const
{
	return Cast<const AMyPawn>(InPawn);
}
// ~Pawn End

// ~Debug input actions Begin
void APC::DebugOne_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void APC::DebugTwo_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void APC::DebugThree_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}
// ~Debug input actions End

void APC::SetTestTimer(const EMyFrameworkPoint InCallingPoint)
{
	UDemoUtilLib::SetupTestTimerIfNecessary(this, TestTimerHandle, InCallingPoint, TimerTestProps, FTimerDelegate::CreateUObject(this, &APC::DoOnTimerTestIfNecessary));
}

void APC::DoOnTimerTestIfNecessary_Implementation()
{
	// Nothing is to be done here
}

// ~Logging Begin
void APC::K2_ThisLog(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogStrings(*Sender, *Format, Args);
}

void APC::K2_ThisLogError(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogErrorStrings(*Sender, *Format, Args);
}

void APC::K2_ThisLogWarn(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogWarnStrings(*Sender, *Format, Args);
}

void APC::ThisLogStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLog(Sender, Format, FormatArgs);
}

void APC::ThisLogErrorStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLogError(Sender, Format, FormatArgs);
}

void APC::ThisLogWarnStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLogWarn(Sender, Format, FormatArgs);
}

void APC::ThisLog(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{	
	UNetUtils::NetPrefixedLog(this, Sender, Format, Args, UDemoUtilLib::GetDefaultLogFlags());
}

void APC::ThisLogError(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{
	UNetUtils::NetPrefixedLogError(this, Sender, Format, Args, UDemoUtilLib::GetDefaultLogFlags());
}

void APC::ThisLogWarn(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{
	UNetUtils::NetPrefixedLogWarn(this, Sender, Format, Args, UDemoUtilLib::GetDefaultLogFlags());
}
// ~Logging End
