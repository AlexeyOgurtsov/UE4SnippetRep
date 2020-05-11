#pragma once

#include "MyObj.generated.h"

UCLASS(BlueprintType)
class UMyObj : public UObject
{
	GENERATED_BODY()

public:
	UMyObj();

	// WARNING!!! We must override it to return TRUE to support replication!!!
	virtual bool IsSupportedForNetworking() const override { return bMySupportedForNetworking; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Replication|Demo|Test")
	void PrintMe() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Replication|Demo|Test")
	void UpdateProps();

	virtual void PrintMe_Implementation();
	virtual void UpdateProps_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Replication|Demo|Test")
	bool bMySupportedForNetworking = true;
};
