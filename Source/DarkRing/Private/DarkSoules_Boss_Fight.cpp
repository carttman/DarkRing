// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkSoules_Boss_Fight.h"

// Sets default values
ADarkSoules_Boss_Fight::ADarkSoules_Boss_Fight()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADarkSoules_Boss_Fight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkSoules_Boss_Fight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADarkSoules_Boss_Fight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

