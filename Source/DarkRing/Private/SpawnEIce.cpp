// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnEIce.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>

#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>

// Sets default values
ASpawnEIce::ASpawnEIce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// HitArea ������Ʈ ����
	HitArea = CreateDefaultSubobject<UBoxComponent>(TEXT("HitArea"));

	// ThrowIce ������Ʈ ����
	ThrowIce = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ThrowIce"));
	//ThrowIce�� HitArea �� �ڽ����� ����  
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

