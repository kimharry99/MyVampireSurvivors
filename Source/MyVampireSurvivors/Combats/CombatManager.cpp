// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"

#include "ICombatAction.h"
#include "Physics/CollisionQueryInfo.h"

void FCombatManager::PerformTargetedAttack(AActor* Target, const ICombatAction& Action)
{
	Action.ExecuteAction(Target);
}

void FCombatManager::PerformAoEAttack(const FCollisionQueryInfo& Info, const ICombatAction& Action)
{
	TArray<AActor*> Victims = FindOverlappedActors(Info, Action.GetInstigator());
	for (auto Victim : Victims)
	{
		Action.ExecuteAction(Victim);
	}
}

TArray<AActor*> FCombatManager::FindOverlappedActors(const FCollisionQueryInfo& Info, const AActor* Instigator)
{
	TArray<AActor*> OverlappedActors;
	if (Instigator)
	{
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(Instigator);

		TArray<FOverlapResult> Overlaps;
		if (const UWorld* World = Instigator->GetWorld())
		{
			World->OverlapMultiByChannel(
				Overlaps,
				Info.Location,
				Info.Rotation,
				Info.CollisionChannel,
				Info.CollisionShape,
				CollisionQueryParams
			);
		}

		for (const auto& Overlap : Overlaps)
		{
			if (AActor* Actor = Overlap.GetActor())
			{
				OverlappedActors.Add(Actor);
			}
		}
	}

	return OverlappedActors;
}
