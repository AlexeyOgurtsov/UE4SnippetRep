#pragma once

#include "Base/Comp.h"
#include "RepComp_PropTest.generated.h"

UCLASS()
class URepComp_PropTest : public UComp
{
	GENERATED_BODY()

public:
	URepComp_PropTest();

	virtual void BeginPlay();

	virtual void PrintMe_Implementation() override;
	virtual void UpdateProps_Implementation() override;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category="Replication|Demo|Test")
	FString RepString;

	FString StringField;
};
