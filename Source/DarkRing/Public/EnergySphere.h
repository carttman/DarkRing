// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergySphere.generated.h"

UCLASS()
class DARKRING_API AEnergySphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnergySphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere)
	class USphereComponent* compSphere;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	UPROPERTY(EditAnywhere)
	class ACppPlayer* player;

	UPROPERTY(EditAnywhere)
	class ADarkSoules_Boss_Fight* boss;

	UPROPERTY(EditAnywhere)
	float randSpeed;
	UPROPERTY(EditAnywhere)
	float randDist;
	UPROPERTY(EditAnywhere)
	FVector playerPos;
	UPROPERTY(EditAnywhere)
	FVector bossPos;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* bombEffect;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* fireEffect;

	UFUNCTION()
	void AutoDestroy();
};
