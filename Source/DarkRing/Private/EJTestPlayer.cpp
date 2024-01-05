// Fill out your copyright notice in the Description page of Project Settings.


#include "EJTestPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"

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
	cam->SetRelativeLocation(FVector(0, 0, 300));

	ConstructorHelpers::FObjectFinder<UInputMappingContext> tempImc(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ThirdPerson/Input/IMC_Default.IMC_Default'"));
	if (tempImc.Succeeded()) {
		imcDafault = tempImc.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputAction> tempIAMouse(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Look.IA_Look'"));
	if (tempIAMouse.Succeeded()) {
		ia_MouseMove = tempIAMouse.Object;
	}
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

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (input) {
		input->BindAction(ia_MouseMove, ETriggerEvent::Triggered, this, &AEJTestPlayer::EnhancedMouse);
	}
}


void AEJTestPlayer::EnhancedMouse(const struct FInputActionValue& value)
{
	FVector2d mouseValue = value.Get< FVector2d > ();
	AddControllerYawInput(mouseValue.X);
	AddControllerPitchInput(mouseValue.Y);

}


