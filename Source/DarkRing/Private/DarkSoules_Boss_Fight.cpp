// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkSoules_Boss_Fight.h"
#include "EJTestPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CppPlayer.h"
#include "BossFSM.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"


// Sets default values
ADarkSoules_Boss_Fight::ADarkSoules_Boss_Fight()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UBossFSM>(TEXT("FSM"));
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = maxTraceSpeed;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Skins/Tier_1_5/MaskedReaper/Mesh/Sevarog_MaskedReaper_GDC.Sevarog_MaskedReaper_GDC'"));
	if (tempMesh.Succeeded()) {
		USkeletalMeshComponent* mesh = GetMesh();
		mesh->SetSkeletalMesh(tempMesh.Object);
	}
}


// Called when the game starts or when spawned
void ADarkSoules_Boss_Fight::BeginPlay()
{
	Super::BeginPlay();

	currHP = maxHP;
	
}

// Called every frame
void ADarkSoules_Boss_Fight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	target = UGameplayStatics::GetActorOfClass(GetWorld(), ACppPlayer::StaticClass());
	if (target != nullptr) {
		FVector playerPos = target->GetActorLocation();
		dir = playerPos - GetActorLocation();
		dir.Normalize();
		FRotator rot = UKismetMathLibrary::MakeRotFromXZ(dir, GetActorUpVector());
		SetActorRotation(rot);

		FVector p = GetActorLocation() + GetActorForwardVector() * DeltaTime * 50;
		
		if (GetDistanceTo(target) >150) SetActorLocation(p);

		
	}
	*/
	

}

// Called to bind functionality to input
void ADarkSoules_Boss_Fight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADarkSoules_Boss_Fight::DamageProcess(int32 damage)
{
	currHP -= damage;
}

