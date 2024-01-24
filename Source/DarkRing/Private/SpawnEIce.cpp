// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEIce.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>

#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>

// Sets default values
ASpawnEIce::ASpawnEIce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// HitArea 컴포넌트 생성
	HitArea = CreateDefaultSubobject<UBoxComponent>(TEXT("HitArea"));
	SetRootComponent(HitArea);
	HitArea->SetCollisionProfileName("OverlapOnlyPawn");
	HitArea->SetRelativeScale3D(FVector(1.7, 1.0, 0.7));
	//(X = 1.700000, Y = 1.000000, Z = 0.700000)
	HitArea->SetRelativeLocation(FVector(30, 0, 0));
	

	// ThrowIce 컴포넌트 생성
	ThrowIce = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ThrowIce"));
	//ThrowIce를 HitArea 의 자식으로 셋팅
	//ThrowIce->SetupAttachment(HitArea);
	ThrowIce->SetRelativeRotation(FRotator(-60, 0, 0));
	ThrowIce->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	ThrowIce->SetRelativeLocation(FVector(0, 0, -30));
	ThrowIce->SetupAttachment(HitArea);

	comProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));
	comProjectile->SetUpdatedComponent(HitArea);
	comProjectile->InitialSpeed = 4000;
	comProjectile->MaxSpeed = 4000;
	comProjectile->bShouldBounce = false;
}

// Called when the game starts or when spawned
void ASpawnEIce::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(10);
}

// Called every frame
void ASpawnEIce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASpawnEIce::AutoDestroy()
{
	Destroy();
}

