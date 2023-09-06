// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "MyProjectile.generated.h"

UCLASS(ABSTRACT)//abstract = Incomplete class, cannot be used by certain functions that deal with actor
class MYPROJECT_API AMyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Impact")
	UNiagaraSystem* ImpactFX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UNiagaraComponent* NiagaraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* AudioComp;
 	//UPROPERTY(EditDefaultsOnly, Category = "Sounds")
 	//USoundBase* FlightSound;
	UPROPERTY(EditDefaultsOnly, Category = "Impact")
	USoundBase* ImpactSound;
	UPROPERTY(EditDefaultsOnly, Category = "Impact")
	float Damage;

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ProjectileExplode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
