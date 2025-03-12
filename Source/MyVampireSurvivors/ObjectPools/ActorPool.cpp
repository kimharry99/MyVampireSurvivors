// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

#include "MyVamSurLogChannels.h"
#include "ObjectPools/PoolableActorInterface.h"

AActorPool::AActorPool(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

AActor* AActorPool::GetPooledActor()
{
	for (int i = 0; i < PooledActors.Num(); ++i)
	{
		AActor* PooledActor = PooledActors[i];
		if (PooledActor)
		{
			IPoolableActorInterface* Poolable = Cast<IPoolableActorInterface>(PooledActor);
			if (!Poolable->IsInUse())
			{
				Poolable->ActivateFromPool();

				return PooledActor;
			}
		}
	}

	return ExpandPoolAndReturnFirst();
}

void AActorPool::SetActorClass(TSubclassOf<AActor> NewActorClass)
{
	checkf(!ActorClass, TEXT("ActorClass is already defined. Don't change ActorClass in runtime."));
	check(NewActorClass);
	check(NewActorClass->ImplementsInterface(UPoolableActorInterface::StaticClass()));

	ActorClass = NewActorClass;
}

void AActorPool::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (AActor* PooledActor : PooledActors)
	{
		if (PooledActor)
		{
			IPoolableActorInterface* Poolable = Cast<IPoolableActorInterface>(PooledActor);
			if (!Poolable->IsInUse())
			{
				Poolable->GetReturnToPoolDelegate()->Unbind();
			}
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AActorPool::ReleaseActor(IPoolableActorInterface* ActorToRelease)
{
	check(ActorToRelease);
	check(PooledActors.Contains(Cast<AActor>(ActorToRelease)));

	ActorToRelease->DeactivateToPool();
}

AActor* AActorPool::ExpandPoolAndReturnFirst()
{
	checkf(ActorClass, TEXT("ActorClass is not defined yet."));

	AActor* FirstNewActor = nullptr;
	if (UWorld* World = GetWorld())
	{
		for (int i = 0; i < ExpansionAmount; ++i)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AActor* NewActor = World->SpawnActor<AActor>(ActorClass, FTransform::Identity, SpawnParams);
			if (NewActor)
			{
				IPoolableActorInterface* Poolable = Cast<IPoolableActorInterface>(NewActor);
				Poolable->DeactivateToPool();
				Poolable->GetReturnToPoolDelegate()->BindUObject(this, &ThisClass::ReleaseActor);
				PooledActors.Add(NewActor);

				if (!FirstNewActor)
				{
					FirstNewActor = NewActor;
				}
			}
		}
	}

	return FirstNewActor;
}
