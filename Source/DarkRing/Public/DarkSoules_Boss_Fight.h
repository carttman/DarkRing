// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DarkSoules_Boss_Fight.generated.h"

UCLASS()
class DARKRING_API ADarkSoules_Boss_Fight : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADarkSoules_Boss_Fight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	AActor* target;

	UPROPERTY()
	FVector dir;

	float maxTraceSpeed = 300;
	float dashDelayTime = 3;
	float currTime = 0;

	UPROPERTY(EditAnywhere)
	int32 currHP = 0;
	int32 maxHP = 10;

public:
	UPROPERTY(EditAnywhere)
	class UBossFSM* fsm;	


	UFUNCTION()
	void DamageProcess(int32 damage);
};
