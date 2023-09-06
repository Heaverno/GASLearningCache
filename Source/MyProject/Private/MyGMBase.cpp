// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGMBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "AI/MyAICharacter.h"
#include "MyAttributeComponent.h"
#include <EngineUtils.h>
#include "MyCharacter.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("my.SpawnBots"), true, TEXT("Enable bot spawn via timer."), ECVF_Cheat);

AMyGMBase::AMyGMBase()
{
	SpawnTimerInterval = 2.0f;
}

void AMyGMBase::KillAll()
{
	for (TActorIterator<AMyAICharacter> It(GetWorld()); It; ++It)
	{
		AMyAICharacter* Bot = *It;
		UMyAttributeComponent* AttriComp = UMyAttributeComponent::GetAttributes(Bot);
		if (AttriComp)
		{
			AttriComp->Kill(this); // @idea: Pass in player for credits?
		}
	}
}

void AMyGMBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AMyGMBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void AMyGMBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawn disabled via CVAR SpawnBots."));
		return;
	}
	int32 NrOfAliveBots = 0;
	for (TActorIterator<AMyAICharacter> It(GetWorld()); It; ++It)
	{
		AMyAICharacter* Bot = *It;
		UMyAttributeComponent* AttriComp = UMyAttributeComponent::GetAttributes(Bot);
		if (AttriComp)
		{
			NrOfAliveBots++;
		}
	}

	float MaxBotCount = 10.0f;
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot at max amount, skipping spawn."));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AMyGMBase::OnQueryCompleted);
	}
}

void AMyGMBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query failed!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0] + FVector {0, 0, 40}, FRotator::ZeroRotator);
	}
}

void AMyGMBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}

void AMyGMBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	AMyCharacter* Player = Cast<AMyCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate_Respawn;
		Delegate_Respawn.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate_Respawn, 2.0f, false);
	}
	UE_LOG(LogTemp, Log, TEXT("Actor killed: Victim is %s, Killer is %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));
}

