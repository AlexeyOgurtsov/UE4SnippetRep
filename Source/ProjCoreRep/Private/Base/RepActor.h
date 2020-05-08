#pragma once

#include "GameFramework/Actor.h"
#include "RepActorTypes.h"
#include "Util/Net/NetUtilsTypes.h"
#include "Engine/EngineTypes.h"
#include "RepActor.generated.h"

UCLASS()
class ARepActor : public AActor
{
	GENERATED_BODY()

public:
	ARepActor();

	/** GetProps*/
	UFUNCTION(BlueprintPure, Category="Props|Demo")
	FRepActorProps GetProps() const { return Props; }

	/** GetProps*/
	UFUNCTION(BlueprintPure, Category="Props|Demo")
	FRepActorTestProps GetTestProps() const { return Props.Test; }

	// ~Logging
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "")
	void PrintMe();
	virtual void PrintMe_Implementation();
	// ~Logging end
	
	// ~Initialization Begin
	virtual void PostInitProperties() override;
	virtual void PostNetInit() override;
	// ~Initialization End

	// ~Gamepaly Begin
	virtual void BeginPlay() override;	
	// ~Gameplay End

	// ~Property Functions Begin		
	virtual void PreNetReceive() override;	
	virtual void PostNetReceive() override;
	// ~Property Functions End

	// ~Role Begin
	virtual void PostNetReceiveRole() override;	
	// ~Role End

	// ~ Owner Begin
	virtual void OnRep_Owner() override;
	// ~ Owner End

	// ~ Movement events Begin
	virtual void OnRep_ReplicateMovement() override;
	// ~ Movement events End

	// ~Channels Begin
	virtual void OnActorChannelOpen(FInBunch& InBunch, class UNetConnection* Connection) override;
	// ~Channels End

	// ~Replication Begin
	virtual void TearOff() override;
	virtual void TornOff() override;	
	// ~Replication End

	// ~Logging utils Begin
	UFUNCTION(BlueprintPure, Category="Demo|Net")
	ENetLogFlags GetDefaultLogFlags() const;
	// ~Logging utils End

protected:
	// ~Logging Begin
	UFUNCTION(BlueprintCallable, Category = "Demo|Net", Meta=(DisplayName = "NetLog"))
	void K2_ThisLog(const FString& Sender, const FString& Format, const TArray<FString>& Args);

	UFUNCTION(BlueprintCallable, Category = "Demo|Net", Meta = (DisplayName = "NetLogError"))
	void K2_ThisLogError(const FString& Sender, const FString& Format, const TArray<FString>& Args);

	UFUNCTION(BlueprintCallable, Category = "Demo|Net", Meta = (DisplayName = "NetLogWarn"))
	void K2_ThisLogWarn(const FString& Sender, const FString& Format, const TArray<FString>& Args);

	void ThisLogStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args);
	void ThisLogErrorStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args);
	void ThisLogWarnStrings(const TCHAR* Sender, const TCHAR* Format, const TArray<FString>& Args);

	void ThisLog(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args);
	void ThisLogError(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args);
	void ThisLogWarn(const TCHAR* Sender, const TCHAR* Format, const TArray<FStringFormatArg>& Args);
	// ~Logging End

	// ~Skeletal Mesh Begin
	UFUNCTION(BlueprintPure, Category = "Mesh|Visual")
	class USkeletalMeshComponent* GetSMComponent() const { return SMComponent; }
	// ~Skeletal Mesh End

	// ~GameFramework Begin

	UFUNCTION(BlueprintNativeEvent, Category = "GameFramework|Demo|Test")
	void BeginPlayTest();
	virtual void BeginPlayTest_Implementation();	

	UFUNCTION(BlueprintNativeEvent, Category = "GameFramework|Demo|Test")
	void TimerTest();
	virtual void TimerTest_Implementation();
	// ~GameFramework End

private:	
	// ~Replication test Begin
	void DoBeginPlayTestIfNecessary();
	void DoPostInitPropsTestIfNecessary();

	void DoTestIfNecessary(EMyFrameworkPoint InCallingPoint, const FRepActorTest& InTest, TFunction<void()> TestFunc);

	bool ShouldDoRepTest(const FRepActorTest& InTest) const;


	// ~Replication test End

	FTimerHandle TestTimerHandle;

	// ~Test Timer Begin
	void SetupTestTimerIfNecessary(EMyFrameworkPoint InCallingPoint, const FRepTimerTest& InTestProps);

	UFUNCTION()
	void DoOnTimerTestIfNecessary();
	// ~Test Timer End

	// ~Props Begin
	void InitMesh();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh|Visual", Meta=(AllowPrivateAccess=true))
	class USkeletalMeshComponent* SMComponent = nullptr;
	// ~Props End

	// ~Test base replicated props Begin
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Replication|Demo|test", Meta = (AllowPrivateAccess = true))
	FString BaseRepProp = TEXT("Uninitialized");
	// ~Test base replicated props End	
	
protected:
	/** Props*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ShowOnlyInnerProperties = true, AllowPrivateAccess = true))
	FRepActorProps Props;
};
