// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PathManager.generated.h"

/**
 * 
 */
UCLASS()
class MAINMAZE_API UPathManager : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "PathManager")
    static void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes,
                               TArray<FString>& OutFileNames);

    /*Prints the data of the given file*/
    UFUNCTION(BlueprintCallable, Category = "PathManager")
    static void PrintData(const FString& File);

    UFUNCTION(BlueprintCallable, Category = "PathManager")
    static void SetPath(const FString& p);

    static std::string GetPath();

private:
    static std::string Path;
};
