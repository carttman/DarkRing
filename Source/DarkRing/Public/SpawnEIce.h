// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEIce.generated.h"

UCLASS()
class DARKRING_API ASpawnEIce : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnEIce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HitArea;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ThrowIce;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* comProjectile;

	float currTime = 0;

public:
	UFUNCTION()
	void AutoDestroy();

};
