// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBase/ActionBaseCharacter.h"
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>


// Sets default values
AActionBaseCharacter::AActionBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.0f);
	BaseEyeHeight = 72.0f;
	GetMesh()->AddLocalOffset(FVector{ 0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() });
	GetMesh()->AddLocalRotation(FRotator{ 0.0f, -90.0f, 0.0f });
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetMesh());
	SpringArmComponent->AddLocalRotation(FRotator{ 0.0f, 90.0f, 0.0f });
	SpringArmComponent->AddLocalOffset(FVector{ 0.0f, 0.0f, BaseEyeHeight + GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() });
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
}

// Called when the game starts or when spawned
void AActionBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AActionBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

