// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayer.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>

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
	
}

// Called every frame
void ACppPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACppPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

