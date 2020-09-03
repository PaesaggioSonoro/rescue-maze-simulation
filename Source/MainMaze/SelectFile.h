// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "SelectFile.generated.h"

/**
 * 
 */
UCLASS()
class MAINMAZE_API USelectFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()	public:

	UFUNCTION(BlueprintCallable, Category = "FileSelector")
	static void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);

	/*Prints the data of the given file*/
	UFUNCTION(BlueprintCallable, Category = "FileSelector")
	void PrintData(const FString& File);
};
