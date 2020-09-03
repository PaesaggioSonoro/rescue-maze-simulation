// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DrawDebugHelpers.h"

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MAINMAZE_API MLX90614
{
public:
	MLX90614(uint8_t addr = 0x5A);
    double read(void);

    //Unreal use only
    void begin(AActor* TMainCharacter);

    UFUNCTION(BlueprintImplementableEvent, Category = "Temperature")
    bool getHot();

private:
    AActor* MainCharacter;
};
