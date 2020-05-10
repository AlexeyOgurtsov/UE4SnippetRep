#pragma once

#include "Base/RepActor.h"
#include "RepActor_PropTest.generated.h"

class URepComp_PropTest;
class URepObj_PropTest;

USTRUCT(BlueprintType)
struct FTestStructToReplicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication")
	FString MyStructName = TEXT("Unnamed");

	// ERROR: Error: Struct members cannot be replicated!
	//UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Replication")
	//FString RepString = TEXT("Uninitialized");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication")
	FString NoRepString = TEXT("Uninitialized");

	FString StringField = TEXT("Uninitialized");

	void TestUpdate();

	void Print(ARepActor* Owner);
};

UCLASS(BlueprintType)
class ARepActor_PropTest : public ARepActor
{
	friend FTestStructToReplicate;

	GENERATED_BODY()

public:
	ARepActor_PropTest();

	// ~Prop Test Config Begin	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PropTest|Demo")
	FRepTestFlags_UpdateObserve OnBeginPlay_UpdateObserve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PropTest|Demo")
	FRepTestFlags_UpdateObserve OnTimer_UpdateObserve;
	// ~Prop Test Config End
	
	UFUNCTION(BlueprintCallable, Category = Demo)
	void DemoUpdateProps_UsingCPPAssign();

	// ~ Test properties Begin

	/**
	* Warning! If Replicated, then DOREPLIFETIME also should be USED!!!
	* Causes WARNING
	*/
	//UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	//FString StringProp_Replicated_NoDoRepLifetime = "StringProp_Replicated_NoDoRepLifetime";

	/**
	* Warning! It's wrong to use DOREPLIEFTIME for the given property because It's not marked as Replicated!!!
	* Causes error
	* Attempt to replicate property 'StrProperty /Script/ProjCoreRep.RepActor:StringProp_DoRepLifetime_NoReplicated' that was not tagged to replicate!
	* Please use 'Replicated' or 'ReplicatedUsing' keyword in the UPROPERTY() declaration.
	*/
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	//FString StringProp_DoRepLifetime_NoReplicated = "StringProp_DoRepLifetime_NoReplicated";

	// WARNING: Failed to find property to replicate (NON-UPROPERTY, trying to replicate)
	//FString StringField = "StringField";
	// ~ Test properties End

	// ~Replication props Begin: Enum
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	ERepTestEnum RepEnum = ERepTestEnum::Uninitialized;
	//ERepTestEnum RepEnumField = ERepTestEnum::Uninitialized;
	// ~Replication props End: Enum

	// ~Replication props Begin
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	float RepFloat = 0.0F;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	int32 RepInt32 = 0;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	FString RepStr;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	FText RepText;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TArray<FString> RepStrArray;

	// WARNING!!! Replicated TSet (s) are NOT supporter: UE 4.24
	//UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	//TSet<FString> RepStrSet;

	// WARNING!!! Replicated TMap (s) are NOT supporter: UE 4.24
	//UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	//TMap<FString, FString> RepStrStrMap;

	//UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	//TMap<FString, int32> RepStrIntMap;
	// ~Replication props End

	// ~Struct Begin
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Replication|Demo|Test", Meta = (AllowPrivateAccess = true))
	FTestStructToReplicate RepTestStruct;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Replication|Demo|Test", Meta = (AllowPrivateAccess = true))
	FTestStructToReplicate TestStruct;
	// ~Struct End

	// ~Components Begin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication|Demo|Test|Component")
	URepComp_PropTest* Comp = nullptr;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Replication|Demo|Test|Component")
	URepComp_PropTest* RepComp = nullptr;
	void InitializeComps();
	// ~Components End

	// ~Objects Begin
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replication|Demo|Test|Component")
	URepObj_PropTest* Obj = nullptr;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Replication|Demo|Test|Component")
	URepObj_PropTest* RepObj = nullptr;
	// ~Objects End

protected:
	void UpdateObserve_IfShould(const FRepTestFlags_UpdateObserve& UpdateObserve);
	
	virtual void BeginPlayTest_Implementation() override;

	virtual void PrintMe_Implementation() override;
	virtual void TimerTest_Implementation() override;
};
