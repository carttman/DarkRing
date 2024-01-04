// Fill out your copyright notice in the Description page of Project Settings.


#include "EJTestPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include "Camera/CameraComponent.h"
// #include "EnhancedInputComponent.h"

// Sets default values
AEJTestPlayer::AEJTestPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Skins/MoonCrystal/Meshes/Aurora_MoonCrystal.Aurora_MoonCrystal'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
	}
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARM"));
	arm->SetupAttachment(RootComponent);

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("CAM"));
	cam->SetupAttachment(arm);
	cam->SetRelativeLocation(FVector(0, 0, 150));

}

// Called when the game starts or when spawned
void AEJTestPlayer::BeginPlay()
{
	Super::BeginPlay();

	
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

// 	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
// 	enhancedInputComponent->BindAction(inputToMove, ETriggerEvent::Triggered, this, &AEJTestPlayer::EnhancedInputMove);
}

// void AEJTestPlayer::EnhancedInputMove(const FInputActionValue& value)
// {
// 
// }

