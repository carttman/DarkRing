// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSwordAura.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
// Sets default values
ASpawnSwordAura::ASpawnSwordAura()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// HitArea 컴포넌트 생성
	HitSword = CreateDefaultSubobject<UBoxComponent>(TEXT("HitSword"));
	SetRootComponent(HitSword);
	HitSword->SetCollisionProfileName("OverlapOnlyPawn");
	HitSword->SetRelativeScale3D(FVector(2, 2, 1));
	//(X = 1.700000, Y = 1.000000, Z = 0.700000)
	HitSword->SetRelativeLocation(FVector(30, 0, 0));

	// ThrowIce 컴포넌트 생성
	ThrowAura = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ThrowIce"));
	//ThrowIce를 HitArea 의 자식으로 셋팅
	//ThrowIce->SetupAttachment(HitArea);
	ThrowAura->SetRelativeRotation(FRotator(0, 0, 0));
	ThrowAura->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	ThrowAura->SetRelativeLocation(FVector(0, 0, 0));
	ThrowAura->SetupAttachment(HitSword);

	comProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILE"));
	comProjectile->SetUpdatedComponent(HitSword);
	comProjectile->InitialSpeed = 4000;
	comProjectile->MaxSpeed = 4000;
	comProjectile->bShouldBounce = false;
}

// Called when the game starts or when spawned
void ASpawnSwordAura::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(1);
}

// Called every frame
void ASpawnSwordAura::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

