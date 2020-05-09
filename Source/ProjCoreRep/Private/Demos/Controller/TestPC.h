#pragma once

#include "Base/PC.h"
#include "Base/RepActorTypes.h"
#include "TestPC.generated.h"

class ATestPawn;

UCLASS(BlueprintType)
class ATestPC : public APC
{
	GENERATED_BODY()

public:
	ATestPC();

	// ~Test RPC calls Begin
	/**
	* The server RPC called:
	* - Always executed ON SERVER;
	* - Can be CALLED both from CLIENT and SERVER;
	*/
	UFUNCTION(Reliable, Server, Category = "RPC|Demo|Replication")
	void ServerTest();

	UFUNCTION(Reliable, Client, Category = "RPC|Demo|Replication")
	void ClientTest();

	UFUNCTION(Reliable, NetMulticast, Category = "RPC|Demo|Replication")
	void MulticastTest();
	// ~Test RPC calls End

	// ~Timer Begin
	virtual void DoOnTimerTestIfNecessary_Implementation() override;
	// ~Timer End

	// ~AActor Begin
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

	virtual void OnPawnBeginPlay_Implementation() override;
	// ~AActor end
	
	// ~Possession begin
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetPawn(APawn* InPawn) override;
	// ~Possession end
	
	// ~Debug actions Begin
	virtual void DebugOne_Implementation() override;
	virtual void DebugTwo_Implementation() override;
	virtual void DebugThree_Implementation() override;
	// ~Debug actions End
	
	// ~Pawn Begin
	UFUNCTION(BlueprintPure, Category = "Pawn")
	ATestPawn* GetTestPawn() const;

	UFUNCTION(BlueprintPure, Category = "Pawn")
	ATestPawn* GetTestPawnChecked() const;

	UFUNCTION(BlueprintPure, Category = "Pawn", Meta=(DisplayName="CastToTestPawn"))
	ATestPawn* K2_CastToTestPawn(APawn* InPawn) const;

	ATestPawn* CastToMyPawn(APawn* InPawn) const;
	const ATestPawn* CastToTestPawn(const APawn* InPawn) const;
	// ~Pawn End
};
