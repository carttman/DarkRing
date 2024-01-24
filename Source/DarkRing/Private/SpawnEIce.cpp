// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEIce.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>

#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>

// Sets default values
ASpawnEIce::ASpawnEIce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// HitArea 컴포넌트 생성
	HitArea = CreateDefaultSubobject<UBoxComponent>(TEXT("HitArea"));

	// ThrowIce 컴포넌트 생성
	ThrowIce = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ThrowIce"));
	//ThrowIce를 HitArea 의 자식으로 셋팅  
	ThrowIce->SetupAttachment(HitArea);
	
}

// Called when the game starts or when spawned
void ASpawnEIce::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnEIce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

