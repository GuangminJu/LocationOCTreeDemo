// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLib.h"

#include "Kismet/GameplayStatics.h"

AActor* UBPLib::GetNearlyActorForeach(const FVector& InLocation, TSubclassOf<AActor> InActorClass,
                                      const UObject* InWorldContextObject, bool bDrawDebug)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UBPLib::GetNearlyActorForeach);

	UWorld* World = InWorldContextObject->GetWorld();
	if (!World)
	{
		return nullptr;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, InActorClass, FoundActors);
	AActor* NearlyActor = nullptr;

	for (AActor* Actor : FoundActors)
	{
		if (!NearlyActor)
		{
			NearlyActor = Actor;
			continue;
		}

		if (FVector::DistSquared(Actor->GetActorLocation(), InLocation) < FVector::DistSquared(
			NearlyActor->GetActorLocation(), InLocation))
		{
			NearlyActor = Actor;
		}

#if !UE_BUILD_SHIPPING
		if (bDrawDebug)
		{
			DrawDebugLine(World, InLocation, Actor->GetActorLocation(), FColor::Blue,
			              false, 0.1f, 0, 5);
		}
#endif
	}

	return NearlyActor;
}

AActor* UBPLib::GetNearlyVisibleActorForeach(const FVector& InLocation,
                                             TSubclassOf<AActor> InActorClass, const UObject* InWorldContextObject,
                                             ECollisionChannel InTraceChannel, bool bDrawDebug)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UBPLib::GetNearlyVisibleActorForeach);

	UWorld* World = InWorldContextObject->GetWorld();
	if (!World)
	{
		return nullptr;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(World, InActorClass, FoundActors);

	FoundActors.Sort([InLocation](const AActor& A, const AActor& B)
	{
		return FVector::DistSquared(A.GetActorLocation(), InLocation) < FVector::DistSquared(
			B.GetActorLocation(), InLocation);
	});

	AActor* NearlyActor = nullptr;

	for (AActor* Actor : FoundActors)
	{
		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams;
		if (World->LineTraceSingleByChannel(HitResult, InLocation, Actor->GetActorLocation(), InTraceChannel,
		                                    CollisionQueryParams))
		{
			if (!HitResult.bBlockingHit || HitResult.GetActor() == Actor)
			{
				NearlyActor = Actor;
				break;
			}
		}
	}

	return NearlyActor;
}
