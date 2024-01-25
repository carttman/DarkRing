// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnSwordAura.generated.h"

UCLASS()
class DARKRING_API ASpawnSwordAura : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnSwordAura();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 궁 검기 맞는 판정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* HitSword;
	
	// 검기의 파티클 
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ThrowAura;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* comProjectile;

};
