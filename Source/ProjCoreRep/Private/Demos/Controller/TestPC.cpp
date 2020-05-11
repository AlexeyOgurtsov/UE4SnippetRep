#include "TestPC.h"
#include "TestPawn.h"
#include "DemoUtils/DemoUtilLib.h"
#include "Util/Core/LogUtilLib.h"

/**
* TODO RPC:
* RPC with return values
*
* TODO Ownership:
* 1. Print default values of bReplicateInstigator
* 2. 
*/

ATestPC::ATestPC()
{
}

void ATestPC::ServerTest_Implementation(const FString& InSender)
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT("Sender={0}"), { InSender });
}

void ATestPC::ClientTest_Implementation(const FString& InSender)
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT("Sender={0}"), { InSender });
}

void ATestPC::MulticastTest_Implementation(const FString& InSender)
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT("Sender={0}"), { InSender });
}

void ATestPC::PostInitProperties()
{
	Super::PostInitProperties();
}

void ATestPC::BeginPlay()
{
	Super::BeginPlay();	
	
	DoTestNetFuncCalls
	(
		TestNetFuncCallProps_Server_BeginPlay,
		TestNetFuncCallProps_Client_BeginPlay,
		TestNetFuncCallProps_NetMulticast_BeginPlay,
		TEXT("BeginPlay"), 
		EMyFrameworkPoint::AtBeginPlay
	);	
}

void ATestPC::DoTestNetFuncCalls
(
	const FRepActorTest& InServerTest,
	const FRepActorTest& InClientTest,
	const FRepActorTest& InNetMulticastTest,
	const TCHAR* const InSender, const EMyFrameworkPoint FrameworkPoint
)
{
	if (UDemoUtilLib::ShouldDoRepTest(this, InServerTest))
	{
		ThisLog(TEXT(__FUNCTION__), TEXT("From \"{0}\" CALLING \"{1}\""), { InSender, TEXT("ServerTest") });
		// Testing that we can perform Server calls from Server itself!
		ServerTest(InSender);
	}

	if (UDemoUtilLib::ShouldDoRepTest(this, InClientTest))
	{
		ThisLog(TEXT(__FUNCTION__), TEXT("From \"{0}\" CALLING \"{1}\""), { InSender, TEXT("ServerTest") });
		// Testing that we can perform Client calls from Server!
		ClientTest(InSender);
	}

	if (UDemoUtilLib::ShouldDoRepTest(this, InNetMulticastTest))
	{
		ThisLog(TEXT(__FUNCTION__), TEXT("From \"{0}\" CALLING \"{1}\""), { InSender, TEXT("ServerTest") });
		// Testing that we can perform NetMulticast calls from Server!
		MulticastTest(InSender);
	}
}

void ATestPC::DoOnTimerTestIfNecessary_Implementation()
{
	M_LOGFUNC();	

	DoTestNetFuncCalls
	(
		TestNetFuncCallProps_Server_Timer,
		TestNetFuncCallProps_Client_Timer,
		TestNetFuncCallProps_NetMulticast_Timer,
		TEXT("Timer"),
		EMyFrameworkPoint::Custom
	);
}

void ATestPC::OnPawnBeginPlay_Implementation()
{
	Super::OnPawnBeginPlay_Implementation();
}
// ~AActor end

// ~Possession begin
void ATestPC::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
}

void ATestPC::OnUnPossess()
{
	Super::OnUnPossess();
}

void ATestPC::SetPawn(APawn* const InPawn)
{
	Super::SetPawn(InPawn);
}
// ~Possession end

// ~Debug actions Begin
void ATestPC::DebugOne_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	ServerTest(TEXT("DebugOne"));
}

void ATestPC::DebugTwo_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ATestPC::DebugThree_Implementation()
{
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}
// ~Debug actions End

// ~Pawn Begin
ATestPawn* ATestPC::GetTestPawn() const
{
	return Cast<ATestPawn>(GetPawn());
}

ATestPawn* ATestPC::GetTestPawnChecked() const
{
	ATestPawn* const P = GetTestPawn();
	checkf(P, TEXT("\"Pawn is to of class \"%s\""), *ATestPawn::StaticClass()->GetName());
	return P;
}

ATestPawn* ATestPC::K2_CastToTestPawn(APawn* const InPawn) const
{
	return Cast<ATestPawn>(InPawn);
}

ATestPawn* ATestPC::CastToMyPawn(APawn* const InPawn) const
{
	return Cast<ATestPawn>(InPawn);
}

const ATestPawn* ATestPC::CastToTestPawn(const APawn* const InPawn) const
{
	return Cast<const ATestPawn>(InPawn);
}
// ~Pawn End

