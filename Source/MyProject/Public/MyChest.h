// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MyGameplayInterface.h"
#include "MyChest.generated.h"

UCLASS()
class MYPROJECT_API AMyChest : public AActor, public IMyGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	AMyChest();
	UPROPERTY(EditAnywhere)
		float LidRotYaw;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* LidMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
