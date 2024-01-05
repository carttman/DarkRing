// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>


// Sets default values
ACppPlayer::ACppPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// imc default ���� �о����
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tempImc(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (tempImc.Succeeded())
	{
		imcDefault = tempImc.Object;
	}

	// ia_jump ���� �о����
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAJump(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));
	if (tempIAJump.Succeeded())
	{
		ia_Jump = tempIAJump.Object;
	}

	// ia_MouseMove ���� �о����
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAMouseMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_MouseMove.IA_MouseMove'"));
	if (tempIAMouseMove.Succeeded())
	{
		ia_MouseMove = tempIAMouseMove.Object;
	}

	// ia_Move ���� �о����
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));
	if (tempIAMove.Succeeded())
	{
		ia_Move = tempIAMove.Object;
	}


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

	// AplayerController ��������
	APlayerController* playerController = Cast<APlayerController>(GetController());

	//subSystem �� ��������
	//UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	// imc_Default�� �߰�����
	subSystem->AddMappingContext(imcDefault, 0);
}

// Called every frame
void ACppPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Enhanced Input BindAction�� ���⿡
void ACppPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (input)
	{
		input->BindAction(ia_Jump, ETriggerEvent::Started, this, &ACppPlayer::EnhancedJump);

		input->BindAction(ia_MouseMove, ETriggerEvent::Triggered, this, &ACppPlayer::EnhancedMouse);

		input->BindAction(ia_Move, ETriggerEvent::Triggered, this, &ACppPlayer::EnhancedMove);

	}

}

void ACppPlayer::MoveAction(FVector2d keyboardInput)
{
	FVector dir = GetActorRightVector() * keyboardInput.X + GetActorForwardVector() * keyboardInput.Y;

	// dir �� ũ�⸦ 1�� �����
	dir.Normalize();

	// dir �������� ��������
	AddMovementInput(dir);

}


void ACppPlayer::InputHorizontal(float value)
{
	moveInput.Y = value;
}

void ACppPlayer::InputVertical(float value)
{
	moveInput.X = value;

}


void ACppPlayer::EnhancedJump()
{
	Jump();
}

void ACppPlayer::EnhancedMouse(const FInputActionValue& value)
{
	FVector2D mouseValue = value.Get<FVector2D>();

	AddControllerYawInput(mouseValue.X);
	AddControllerPitchInput(mouseValue.Y);
}

void ACppPlayer::EnhancedMove(const FInputActionValue& value)
{
	FVector2D keyboardValue = value.Get<FVector2D>();

	MoveAction(keyboardValue);

}
