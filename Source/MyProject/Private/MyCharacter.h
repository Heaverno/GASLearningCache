// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyInteractComponent.h"
#include "MyAttributeComponent.h"
#include "ActionComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMyAttributeComponent* AttriComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UActionComponent* ActionComp;

	UMyInteractComponent* InteractComp;

	UPROPERTY(EditDefaultsOnly, Category = "Impact")
	FLinearColor HitColor;

	UPROPERTY(EditDefaultsOnly, Category = "Impact")
	float FlashSpeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	void FMoveFwd(float val);
	void FMoveRt(float val);
	void SprintStart();
	void SprintStop();
	void PrimaryAtk(); void SkillQ(); void SkillR();
	void PrimaryInteract();
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

public:	
	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
	
	virtual FVector GetPawnViewLocation() const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
