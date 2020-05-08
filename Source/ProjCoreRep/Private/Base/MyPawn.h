#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class APC;

UCLASS()
class AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

	UFUNCTION(BlueprintPure, Category="BeginPlay|GameFramework")
	bool IsBeginPlayCalled() const { return bBeginPlayCalled; }

	// ~Actor Begin
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	// ~Actor End

	// ~Controller Begin
	UFUNCTION(BlueprintPure, Category = "Possession")
	APC* GetPC() const;

	UFUNCTION(BlueprintPure, Category = "Possession")
	APC* GetPCChecked() const;

	UFUNCTION(BlueprintPure, Category = "Possession", Meta=(DisplayName="CastToPC"))
	APC* K2_CastToPC(AController* InController) const;

	APC* CastToPC(AController* InController) const;
	const APC* CastToPC(const AController* InController) const;
	// ~Controller End
	
	bool bBeginPlayCalled = false;

protected:
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
};
