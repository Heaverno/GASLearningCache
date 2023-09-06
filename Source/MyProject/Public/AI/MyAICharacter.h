// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyAttributeComponent.h"
#include "MyAICharacter.generated.h"

class UPawnSensingComponent;
class UUserWidget;
class UMyGameWorldWidget;

UCLASS()
class MYPROJECT_API AMyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyAICharacter();

protected:
	UMyGameWorldWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMyAttributeComponent* AttriComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

	void SetTargetActor(AActor* NewTarget);
	virtual void PostInitializeComponents() override;

};
