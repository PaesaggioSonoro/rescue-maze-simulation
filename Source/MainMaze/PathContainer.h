// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "Containers/UnrealString.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PathContainer.generated.h"


using namespace std;
/**
 * 
 */
UCLASS()
class MAINMAZE_API UPathContainer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "PathContainer")
    static void setPath(const FString& p);

    static string getPath();

private:
    static string path;
};
