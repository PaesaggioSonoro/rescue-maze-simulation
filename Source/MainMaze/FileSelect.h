// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "FileSelect.generated.h"

UCLASS()
class MAINMAZE_API AFileSelect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFileSelect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "FilePicker")
	void OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes, TArray<FString>& OutFileNames);

	/*Prints the data of the given file*/
	UFUNCTION(BlueprintCallable, Category = "FilePicker")
	void PrintData(const FString& File);
};
