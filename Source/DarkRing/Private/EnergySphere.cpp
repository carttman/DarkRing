// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergySphere.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "CppPlayer.h"
#include "DarkSoules_Boss_Fight.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystem.h>
#include <../../../../../../../Source/Editor/Cascade/Classes/CascadeParticleSystemComponent.h>

// Sets default values
AEnergySphere::AEnergySphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	SetRootComponent(compSphere);

	compSphere->SetRelativeScale3D(FVector(0.7));

	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(RootComponent);
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	if (tempMesh.Succeeded()) {
		compMesh->SetStaticMesh(tempMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem>tempEffect(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (tempEffect.Succeeded()) {
		bombEffect = tempEffect.Object;
	}

	fireEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	fireEffect->SetupAttachment(RootComponent);

// 	ConstructorHelpers::FObjectFinder<UCascadeParticleSystemComponent> tempFire(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'"));
// 	if (tempFire.Succeeded()) {
// 		fireEffect = tempFire.Object;
// 	}/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'
	
	AActor* findPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), ACppPlayer::StaticClass());
	player = Cast<ACppPlayer>(findPlayer);
	AActor* findBoss = UGameplayStatics::GetActorOfClass(GetWorld(), ADarkSoules_Boss_Fight::StaticClass());
	boss = Cast<ADarkSoules_Boss_Fight>(findBoss);
}

// Called when the game starts or when spawned
void AEnergySphere::BeginPlay()
{
	Super::BeginPlay();
	randSpeed = FMath::RandRange(1.5f, 2.5f);
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("AutoDestroy"), 5, false);






}

// Called every frame
void AEnergySphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player != nullptr) {

		//UE_LOG(LogTemp, Warning, TEXT("%f"), randAngle);
		//FVector dir = player->GetActorLocation() - GetActorLocation();
		
		FVector p = GetActorLocation() + ( - GetActorForwardVector()) * DeltaTime * 300;
	
		SetActorLocation(p);

	}


// 	FRotator rot = FRotator(0, randAngle, 0);
// 	FVector randDir = UKismetMathLibrary::GetForwardVector(rot);
	randDist = FMath::RandRange(100.0f, 1500.0f);
	//FVector spawnPos = GetActorLocation() * randDir;
	//SetActorLocation(FVector(randAngle,0,50));


}

void AEnergySphere::AutoDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("destroy"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bombEffect, GetActorLocation(), GetActorRotation());
	Destroy();

}

