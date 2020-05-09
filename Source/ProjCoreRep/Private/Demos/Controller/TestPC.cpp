#include "TestPC.h"
#include "TestPawn.h"
#include "DemoUtils/DemoUtilTypes.h"
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

void ATestPC::ServerTest_Implementation()
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ATestPC::ClientTest_Implementation()
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ATestPC::MulticastTest_Implementation()
{
	M_LOGFUNC();
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
}

void ATestPC::PostInitProperties()
{
	Super::PostInitProperties();
}

void ATestPC::BeginPlay()
{
	Super::BeginPlay();	

	{
		if (HasAuthority())
		{
			// Testing that we can perform Server calls from Server itself!
			ServerTest();

			// Testing that we can perform Client calls from Server!
			//ClientTest();

			// Testing that we can perform NetMulticast calls from Server!
			//MulticastTest();
		}
	}
}

void ATestPC::DoOnTimerTestIfNecessary_Implementation()
{
	M_LOGFUNC();	
	ThisLog(TEXT(__FUNCTION__), TEXT(""), {});
	// @TODO
}

void ATestPC::OnPawnBeginPlay_Implementation()
{
	Super::OnPawnBeginPlay_Implementation();

	if (HasAuthority())
	{
		// Testing that we can perform Server calls from Server itself!
		ServerTest();

		// Testing that we can perform Client calls from Server!
		ClientTest();

		// Testing that we can perform NetMulticast calls from Server!
		MulticastTest();
	}
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
	ServerTest();
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

