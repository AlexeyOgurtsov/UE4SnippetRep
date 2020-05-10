#include "Comp.h"
#include "Util\Core\LogUtilLib.h"
#include "Util\Net\NetUtils.h"
#include "DemoUtils\DemoUtilLib.h"

/**
* Replication test: 
* Activate state replication.
*/

UComp::UComp()
{
	SetIsReplicatedByDefault(true); // WARNING!!! Components are NOT replicated by default!!!

	UNetUtils::LogComponentNetVars(this);
}

void UComp::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}

void UComp::PrintMe_Implementation()
{
}

void UComp::UpdateProps_Implementation()
{
	
}
