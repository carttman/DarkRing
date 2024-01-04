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

	//Skeletal Mesh 읽어오기
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Skins/GlacialEmpress/Meshes/Aurora_GlacialEmpress.Aurora_GlacialEmpress'"));

	//tempMesh를 잘 불러왔다면 
	if (tempMesh.Succeeded())
	{
		// Mesh 에 Skeletal Mesh 셋팅
		USkeletalMeshComponent* mesh = GetMesh();
		mesh->SetSkeletalMesh(tempMesh.Object);
	}

	// Mesh 의 위치 값과 회전값을 셋팅
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); //pitch, yaw, roll

	//SpringArm 컴포넌트 생성
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	//springArm 을 RootComponent 의 자식 (루프 컴포넌트는 디폴트 기본 자식임)
	springArm->SetupAttachment(RootComponent);
	//springArm 위치를 바꾸자
	springArm->SetRelativeLocation(FVector(0, 0, 90));
	//springArm 각도 변경
	springArm->SetRelativeRotation(FRotator(-30, 0, 0));

	//camera 컴포넌트 생성
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	//camera 를 springArm 의 자식으로 셋팅
	camera->SetupAttachment(springArm);

	
}

// Called when the game starts or when spawned
void ACppPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 움직이는 속력을 moveSpeed 로 하자
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	// Controller 의 회전값을 따라 갈지 여부
	bUseControllerRotationYaw = true;
	springArm->bUsePawnControlRotation = true;

	// 카메라 상/하 회전값을 제한 (min, max 설정)
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	playerCon->PlayerCameraManager->ViewPitchMin = -60;
	playerCon->PlayerCameraManager->ViewPitchMax = 60;

	//APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//camManager->ViewPitchMin = -60;
	//camManager->ViewPitchMax = 60;

	//점프 횟수 제한
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

	// 마우스 좌우 움직일 때
	PlayerInputComponent->BindAxis(TEXT("MouseX"), this, &ACppPlayer::InputMouseX);

	// 마우스 상하 움직일 때
	PlayerInputComponent->BindAxis(TEXT("MouseY"), this, &ACppPlayer::InputMouseY);

	// 스페이스바 눌렀을 때 
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACppPlayer::InputJump);
	PlayerInputComponent->BindAction(TEXT("StopJumping"), IE_Released, this, &ACppPlayer::InputJump);

	
}

void ACppPlayer::MoveAction()
{
	FVector dir = GetActorRightVector() * moveInput.Y + GetActorForwardVector() * moveInput.X;

	// dir 의 크기를 1로 만든다
	dir.Normalize();

	// dir 방향으로 움직여라
	AddMovementInput(dir);

}

void ACppPlayer::RotateAction()
{
	// 나의 회전 yaw (z축) 값 셋팅
	SetActorRotation(FRotator(0, mx, 0));

	//spring arm 의 회전 pitch (y축) 값 셋팅
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
