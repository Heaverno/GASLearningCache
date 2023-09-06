// Fill out your copyright notice in the Description page of Project Settings.


#include "MyChest.h"

// Sets default values
AMyChest::AMyChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(RootComponent);

	LidRotYaw = 66;
}

void AMyChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->AddRelativeRotation(FRotator(0, LidRotYaw, 0));
}


// Called when the game starts or when spawned
void AMyChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

