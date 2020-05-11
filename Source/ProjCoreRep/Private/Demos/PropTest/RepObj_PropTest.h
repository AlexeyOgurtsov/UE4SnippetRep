#pragma once

#include "Base/MyObj.h"
#include "RepObj_PropTest.generated.h"

UCLASS(BlueprintType)
class URepObj_PropTest : public UMyObj
{
	GENERATED_BODY()

public:
	URepObj_PropTest();

	// Replicate key needs to be changed each time object needs to be replicated
	int32 GetRepKey() const;

	virtual void PrintMe_Implementation() override;
	virtual void UpdateProps_Implementation() override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Rep|Demo|Utils")
	FString RepString = "";

	FString StringField = "";

	int32 RepKey = 0;
};
