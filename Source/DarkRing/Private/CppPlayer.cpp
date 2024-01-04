// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>


// Sets default values
ACppPlayer::ACppPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Skeletal Mesh �о����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Skins/GlacialEmpress/Meshes/Aurora_GlacialEmpress.Aurora_GlacialEmpress'"));

	//tempMesh�� �� �ҷ��Դٸ� 
	if (tempMesh.Succeeded())
	{
		// Mesh �� Skeletal Mesh ����
		USkeletalMeshComponent* mesh = GetMesh();
		mesh->SetSkeletalMesh(tempMesh.Object);
	}

	// Mesh �� ��ġ ���� ȸ������ ����
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); //pitch, yaw, roll

	//SpringArm ������Ʈ ����
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	//springArm �� RootComponent �� �ڽ� (���� ������Ʈ�� ����Ʈ �⺻ �ڽ���)
	springArm->SetupAttachment(RootComponent);
	//springArm ��ġ�� �ٲ���
	springArm->SetRelativeLocation(FVector(0, 0, 90));
	//springArm ���� ����
	springArm->SetRelativeRotation(FRotator(-30, 0, 0));

	//camera ������Ʈ ����
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	//camera �� springArm �� �ڽ����� ����
	camera->SetupAttachment(springArm);

	
}

// Called when the game starts or when spawned
void ACppPlayer::BeginPlay()
{
	Super::BeginPlay();

	// �����̴� �ӷ��� moveSpeed �� ����
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	// Controller �� ȸ������ ���� ���� ����
	bUseControllerRotationYaw = true;
	springArm->bUsePawnControlRotation = true;

	// ī�޶� ��/�� ȸ������ ���� (min, max ����)
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	playerCon->PlayerCameraManager->ViewPitchMin = -60;
	playerCon->PlayerCameraManager->ViewPitchMax = 60;

	//APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//camManager->ViewPitchMin = -60;
	//camManager->ViewPitchMax = 60;

	//���� Ƚ�� ����
	JumpMaxCount = 2;

}

// Called every frame
void ACppPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveAction();

}

// Called to bind functionality to input
void ACppPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// A, D
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACppPlayer::InputHorizontal);

	// W, S
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACppPlayer::InputVertical);

	// ���콺 �¿� ������ ��
	PlayerInputComponent->BindAxis(TEXT("MouseX"), this, &ACppPlayer::InputMouseX);

	// ���콺 ���� ������ ��
	PlayerInputComponent->BindAxis(TEXT("MouseY"), this, &ACppPlayer::InputMouseY);

	// �����̽��� ������ �� 
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACppPlayer::InputJump);
	PlayerInputComponent->BindAction(TEXT("StopJumping"), IE_Released, this, &ACppPlayer::InputJump);

	
}

void ACppPlayer::MoveAction()
{
	FVector dir = GetActorRightVector() * moveInput.Y + GetActorForwardVector() * moveInput.X;

	// dir �� ũ�⸦ 1�� �����
	dir.Normalize();

	// dir �������� ��������
	AddMovementInput(dir);

}

void ACppPlayer::RotateAction()
{
	// ���� ȸ�� yaw (z��) �� ����
	SetActorRotation(FRotator(0, mx, 0));

	//spring arm �� ȸ�� pitch (y��) �� ����
	springArm->SetRelativeRotation(FRotator(my, 0, 0));

}

void ACppPlayer::InputHorizontal(float value)
{
	moveInput.Y = value;
}

void ACppPlayer::InputVertical(float value)
{
	moveInput.X = value;

}

void ACppPlayer::InputMouseX(float value)
{
	AddControllerYawInput(value);

}

void ACppPlayer::InputMouseY(float value)
{
	AddControllerPitchInput(value);

}

void ACppPlayer::InputJump()
{
	Jump();
	
}
