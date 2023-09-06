// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "MyAttributeComponent.h"
#include "MyTarget.generated.h"

//using namespace UF;

UCLASS()
class MYPROJECT_API AMyTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTarget();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMyAttributeComponent* AttriComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);
	UFUNCTION(BlueprintCallable)
	void TriggerFireImpulse();

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
