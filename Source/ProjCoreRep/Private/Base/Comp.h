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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Replication|Demo|Test")
	void PrintMe() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Replication|Demo|Test")
	void UpdateProps();

	virtual void PrintMe_Implementation();
	virtual void UpdateProps_Implementation();
};
