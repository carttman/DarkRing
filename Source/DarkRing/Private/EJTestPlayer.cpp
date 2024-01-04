// Fill out your copyright notice in the Description page of Project Settings.


#include "EJTestPlayer.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>

// Sets default values
AEJTestPlayer::AEJTestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEJTestPlayer::BeginPlay()
{
	Super::BeginPlay();

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Skins/MoonCrystal/Meshes/Aurora_MoonCrystal.Aurora_MoonCrystal'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARM"));
	arm->SetupAttachment(RootComponent);
}

// Called every frame
void AEJTestPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEJTestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

