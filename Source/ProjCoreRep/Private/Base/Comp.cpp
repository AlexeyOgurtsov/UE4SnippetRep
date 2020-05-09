#include "Comp.h"
#include "Util\Core\LogUtilLib.h"
#include "Util\Net\NetUtils.h"
#include "DemoUtils\DemoUtilLib.h"

UComp::UComp()
{
	UNetUtils::LogComponentNetVars(this);
}

void UComp::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
}
