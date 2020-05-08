#pragma once

#include "Components\ActorComponent.h"
#include "Comp.generated.h"

UCLASS(BlueprintType)
class UComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UComp();

	virtual void BeginPlay();
};
