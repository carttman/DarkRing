// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergySphere.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "CppPlayer.h"
#include "DarkSoules_Boss_Fight.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystem.h>

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

	ConstructorHelpers::FObjectFinder<UStaticMesh>tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	if (tempMesh.Succeeded()) {
		compMesh->SetStaticMesh(tempMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem>tempEffect(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (tempEffect.Succeeded()) {
		bombEffect = tempEffect.Object;
	}
	
	AActor* findPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), ACppPlayer::StaticClass());
	player = Cast<ACppPlayer>(findPlayer);
	AActor* findBoss = UGameplayStatics::GetActorOfClass(GetWorld(), ADarkSoules_Boss_Fight::StaticClass());
	boss = Cast<ADarkSoules_Boss_Fight>(findBoss);
}

// Called when the game starts or when spawned
void AEnergySphere::BeginPlay()
{
	Super::BeginPlay();
	randAngle = FMath::RandRange(1.5f, 2.5f);
	UKismetSystemLibrary::K2_SetTimer(this, TEXT("AutoDestroy"), 5, false);
}

// Called every frame
void AEnergySphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//  	playerPos = player->GetActorLocation();
//  	bossPos = boss->GetActorLocation();

	//UE_LOG(LogTemp, Warning, TEXT("%f"), randAngle);
	FVector dir = player->GetActorLocation() - GetActorLocation();
	FVector p = GetActorLocation() + dir * DeltaTime * randAngle;
	SetActorLocation(p);






// 
//  	FVector dir = playerPos - bossPos;
// 	FVector p = bossPos + dir.Normalize() * DeltaTime * 300;
// 	SetActorLocation(p);
// 
// 	FRotator rot = FRotator(0, randAngle, 0);
// 	FVector randDir = UKismetMathLibrary::GetForwardVector(rot);
	//float randDist = FMath::RandRange(100.0f, 1500.0f);
	//FVector spawnPos = GetActorLocation() * randDir;
	//SetActorLocation(FVector(randAngle,0,50));


}

void AEnergySphere::AutoDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("destroy"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bombEffect, GetActorLocation(), GetActorRotation());
	Destroy();

}

