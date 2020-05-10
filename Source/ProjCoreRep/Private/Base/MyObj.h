#pragma once

#include "MyObj.generated.h"

UCLASS(BlueprintType)
class UMyObj : public UObject
{
	GENERATED_BODY()

public:
	UMyObj();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Replication|Demo|Test")
	void PrintMe() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Replication|Demo|Test")
	void UpdateProps();

	virtual void PrintMe_Implementation();
	virtual void UpdateProps_Implementation();
};
