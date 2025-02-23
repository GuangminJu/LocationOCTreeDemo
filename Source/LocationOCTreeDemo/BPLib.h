// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BPLib.generated.h"

/**
 * 
 */
UCLASS()
class LOCATIONOCTREEDEMO_API UBPLib : public UObject
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "BPLib", meta = (WorldContext = "InWorldContextObject"))
	static AActor* GetNearlyActorForeach(const FVector& InLocation, TSubclassOf<AActor> InActorClass,
	                                     const UObject* InWorldContextObject, bool bDrawDebug = false);

	UFUNCTION(BlueprintCallable, Category = "BPLib", meta = (WorldContext = "InWorldContextObject"))
	static AActor* GetNearlyVisibleActorForeach(const FVector& InLocation, TSubclassOf<AActor> InActorClass,
										 const UObject* InWorldContextObject, ECollisionChannel InTraceChannel, bool bDrawDebug = false);
};
