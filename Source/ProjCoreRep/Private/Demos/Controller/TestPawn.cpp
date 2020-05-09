#include "TestPawn.h"
#include "TestPC.h"
#include "DemoUtils/DemoUtilTypes.h"
#include "Util/Core/LogUtilLib.h"

ATestPawn::ATestPawn()
{
}

// ~Actor Begin
void ATestPawn::PostInitProperties()
{
	Super::PostInitProperties();
}

void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
}
// ~Actor End

// ~Controller Begin
ATestPC* ATestPawn::GetTestPC() const
{
	return Cast<ATestPC>(GetController());
}

ATestPC* ATestPawn::GetTestPCChecked() const
{
	ATestPC* const P = GetTestPC();
	checkf(P, TEXT("\"Controller must be of class \"%s\""), *ATestPC::StaticClass()->GetName());
	return P;
}

ATestPC* ATestPawn::K2_CastToTestPC(AController* const InController) const
{
	return Cast<ATestPC>(InController);
}

ATestPC* ATestPawn::CastToPC(AController* const InController) const
{
	return Cast<ATestPC>(InController);
}

const ATestPC* ATestPawn::CastToTestPC(const AController* const InController) const
{
	return Cast<const ATestPC>(InController);
}
// ~Controller End
