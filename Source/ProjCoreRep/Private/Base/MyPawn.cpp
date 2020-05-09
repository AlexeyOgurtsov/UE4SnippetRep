#include "MyPawn.h"
#include "PC.h"
#include "Util\Core\LogUtilLib.h"
#include "Util\Net\NetUtils.h"
#include "DemoUtils\DemoUtilLib.h"

AMyPawn::AMyPawn()
{
}

// ~AActor begin
void AMyPawn::PostInitProperties()
{
	M_LOGFUNC();
	Super::PostInitProperties();
}

void AMyPawn::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();

	UNetUtils::LogNetVars(this);

	bBeginPlayCalled = true;
	if(APC* PC = GetPC())
	{
		PC->OnPawnBeginPlay();
	}
}
// ~AActor end

// ~Controller Begin
APC* AMyPawn::GetPC() const
{
	return CastToPC(GetController());
}

APC* AMyPawn::GetPCChecked() const
{
	APC* const PC = GetPC();
	checkf(PC, TEXT("\"PC is to of class \"%s\""), *APC::StaticClass()->GetName());
	return PC;
}

APC* AMyPawn::K2_CastToPC(AController* const InController) const
{
	return CastToPC(InController);
}

APC* AMyPawn::CastToPC(AController* const InController) const
{
	return Cast<APC>(InController);
}

const APC* AMyPawn::CastToPC(const AController* const InController) const
{
	return Cast<const APC>(InController);
}
// ~Controller End

// ~Logging Begin
void AMyPawn::K2_ThisLog(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogStrings(*Sender, *Format, Args);
}

void AMyPawn::K2_ThisLogError(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogErrorStrings(*Sender, *Format, Args);
}

void AMyPawn::K2_ThisLogWarn(const FString& Sender, const FString& Format, const TArray<FString>& Args)
{
	ThisLogWarnStrings(*Sender, *Format, Args);
}

void AMyPawn::ThisLogStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLog(Sender, Format, FormatArgs);
}

void AMyPawn::ThisLogErrorStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLogError(Sender, Format, FormatArgs);
}

void AMyPawn::ThisLogWarnStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args)
{
	const TArray<FStringFormatArg> FormatArgs = UDemoUtilLib::StringArrayToFormatArgs(Args);
	ThisLogWarn(Sender, Format, FormatArgs);
}

void AMyPawn::ThisLog(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{	
	UNetUtils::NetPrefixedLog(this, Sender, Format, Args, UDemoUtilLib::GetDefaultLogFlags());
}

void AMyPawn::ThisLogError(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{
	UNetUtils::NetPrefixedLogError(this, Sender, Format, Args, UDemoUtilLib::GetDefaultLogFlags());
}

void AMyPawn::ThisLogWarn(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args)
{
	UNetUtils::NetPrefixedLogWarn(this, Sender, Format, Args, UDemoUtilLib::GetDefaultLogFlags());
}
// ~Logging End
