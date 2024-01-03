// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayer.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>

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

