#pragma once

#include "Base/MyPawn.h"
#include "Base/RepActorTypes.h"
#include "TestPawn.generated.h"

class ATestPC;

UCLASS(BlueprintType)
class ATestPawn : public AMyPawn
{
	GENERATED_BODY()

public:
	ATestPawn();

	// ~Actor Begin
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	// ~Actor End

	// ~Controller Begin
	UFUNCTION(BlueprintPure, Category = "Possession")
	ATestPC* GetTestPC() const;

	UFUNCTION(BlueprintPure, Category = "Possession")
	ATestPC* GetTestPCChecked() const;

	UFUNCTION(BlueprintPure, Category = "Possession", Meta=(DisplayName="CastToTestPC"))
	ATestPC* K2_CastToTestPC(AController* InController) const;

	ATestPC* CastToPC(AController* InController) const;
	const ATestPC* CastToTestPC(const AController* InController) const;
	// ~Controller End
};
