#pragma once

#include "GameFramework/PlayerController.h"
#include "PC.generated.h"

class AMyPawn;

UCLASS(BlueprintType)
class APC : public APlayerController
{
	GENERATED_BODY()

public:
	APC();

	// ~AActor begin
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintNativeEvent, Category = "GameFramework|BeginPlay")
	void OnPawnBeginPlay();
	virtual void OnPawnBeginPlay_Implementation();
	// ~AActor end
	
	// ~AActor helpers
	UFUNCTION(BlueprintPure, Category = "GameFramework|BeginPlay")
	bool IsBeginPlayCalled() const { return bBeginPlayCalled; }
	// ~AActor helpers

	// ~Possession begin
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetPawn(APawn* InPawn) override;
	// ~Possession end
	
	// ~Pawn Begin
	UFUNCTION(BlueprintPure, Category = "Pawn")
	AMyPawn* GetMyPawn() const;

	UFUNCTION(BlueprintPure, Category = "Pawn")
	AMyPawn* GetMyPawnChecked() const;

	UFUNCTION(BlueprintPure, Category = "Pawn", Meta=(DisplayName="CastToMyPawn"))
	AMyPawn* K2_CastToMyPawn(APawn* InPawn) const;

	AMyPawn* CastToMyPawn(APawn* InPawn) const;
	const AMyPawn* CastToMyPawn(const APawn* InPawn) const;
	// ~Pawn End
	
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

	UFUNCTION(BlueprintNativeEvent, Category = InputEvents)
	void DebugOne();
	virtual void DebugOne_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = InputEvents)
	void DebugTwo();
	virtual void DebugTwo_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = InputEvents)
	void DebugThree();
	virtual void DebugThree_Implementation();

private:
	bool bBeginPlayCalled = false;
};
