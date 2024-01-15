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
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "PlayerAnim.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h"
#include "DarkSoules_Boss_Fight.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
ACppPlayer::ACppPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// imc default 파일 읽어오자
	ConstructorHelpers::FObjectFinder<UInputMappingContext> tempImc(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (tempImc.Succeeded())
	{
		imcDefault = tempImc.Object;
	}

	// ia_jump 파일 읽어오자
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAJump(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Jump.IA_Jump'"));
	if (tempIAJump.Succeeded())
	{
		ia_Jump = tempIAJump.Object;
	}

	// ia_MouseMove 파일 읽어오자
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAMouseMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_MouseMove.IA_MouseMove'"));
	if (tempIAMouseMove.Succeeded())
	{
		ia_MouseMove = tempIAMouseMove.Object;
	}

	// ia_Move 파일 읽어오자
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Move.IA_Move'"));
	if (tempIAMove.Succeeded())
	{
		ia_Move = tempIAMove.Object;
	}

	// ia_Attack 파일 읽어오자
	ConstructorHelpers::FObjectFinder<UInputAction> tempIAAttack(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Attack.IA_Attack'"));
	if (tempIAAttack.Succeeded())
	{
		ia_Attack = tempIAAttack.Object;
	}

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

	//-----------------------------------------------------------
	sceneAttack = CreateDefaultSubobject<USceneComponent> (TEXT("SCENE"));
	sceneAttack->SetupAttachment(GetMesh());
	sceneAttack->SetRelativeLocation(FVector(-30, 0, 0));

}

// Called when the game starts or when spawned
void ACppPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 움직이는 속력을 moveSpeed 로 하자
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	// Controller 의 회전값을 따라 갈지 여부
	//bUseControllerRotationYaw = false;
	//springArm->bUsePawnControlRotation = true;

	// 카메라 상/하 회전값을 제한 (min, max 설정)
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	playerCon->PlayerCameraManager->ViewPitchMin = -60;
	playerCon->PlayerCameraManager->ViewPitchMax = 60;

	//APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//camManager->ViewPitchMin = -60;
	//camManager->ViewPitchMax = 60;

	//점프 횟수 제한
	JumpMaxCount = 1;

	// AplayerController 가져오자
	APlayerController* playerController = Cast<APlayerController>(GetController());

	//subSystem 을 가져오자
	//UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	// imc_Default를 추가하자
	subSystem->AddMappingContext(imcDefault, 0);

	
}

// Called every frame
void ACppPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//업데이트 콤보의 델타타임 증가시켜라 / 초를 증가시켜라
	UpdateCombo(DeltaTime);

}

// Enhanced Input BindAction은 여기에
void ACppPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (input)
	{
		input->BindAction(ia_Jump, ETriggerEvent::Started, this, &ACppPlayer::EnhancedJump);

		input->BindAction(ia_MouseMove, ETriggerEvent::Triggered, this, &ACppPlayer::EnhancedMouse);

		input->BindAction(ia_Move, ETriggerEvent::Triggered, this, &ACppPlayer::EnhancedMove);

		input->BindAction(ia_Attack, ETriggerEvent::Triggered, this, &ACppPlayer::EnhancedAttck);
	}

}

void ACppPlayer::MoveAction(FVector2d keyboardInput)
{
	FRotator rot = GetControlRotation();
	FVector forward = UKismetMathLibrary::GetForwardVector(rot);
	FVector right = UKismetMathLibrary::GetRightVector(rot);

	FVector dir = right * keyboardInput.X + forward * keyboardInput.Y;

	// dir 의 크기를 1로 만든다
	dir.Normalize();


	// dir 방향으로 움직여라


	//--------------------- 플레이어가 보스 뚫고지나가지 않게(가까이 붙지 않게)

	
	
	AActor* boss = UGameplayStatics::GetActorOfClass(GetWorld(), ADarkSoules_Boss_Fight::StaticClass());
	if (boss != nullptr) {                      //보스 죽고나서도 에러 안나게
		FVector distance = GetActorLocation() - boss->GetActorLocation();
		float dist = abs(distance.Length());
		if (dist > 120) AddMovementInput(dir);           //이거만 적으면 한번 붙고나서는 못움직임
		else AddMovementInput(-forward);                 //붙으면 뒤로 살짝 빼서 움직일 수 있게

	}
	else AddMovementInput(dir);

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

void ACppPlayer::EnhancedAttck(const struct FInputActionValue& value)
{
	// 만약 공중에 있는 상태라면 공격 못하도록 바로 리턴
	if (GetCharacterMovement()->IsFalling()) return;

	// 애니메이션을 플레이 하고있는가? 불 변수 선언
	bool playAnimation = false;

	
	// 섹션 점프를 하기위한 sectionName 선언
	FName sectionName = TEXT("");
	
	//만약 combo 카운트가 0일 때 
	if(comboCnt == 0)
	{
		//combo 카운트를 1 증가하고  콤보 현재시간을 0으로 
		comboCnt++;
		comboCurrTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("%d타"), comboCnt);

		//공격 몽타주 섹션 실행
		playAnimation = true;
		sectionName = TEXT("Attack1");

		//플레이어 이동 정지
		GetCharacterMovement()->SetMovementMode(MOVE_None);
		//공격하고 있을 때 점프 막자
		GetCharacterMovement()->SetJumpAllowed(false);

		
		
	}

	//만약 combo 카운트가 1일 때 
	else if(comboCnt == 1)
	{
		// 만약 콤보현재시간이 최소시간보다 작거나 같고 and 최대시간이 작거나 같을 때
		if (comboMinTime <= comboCurrTime && comboCurrTime <= comboMaxTime)
		{
			// 콤보 카운트 1 증가시키고 현재시간 0 으로 초기화 
			comboCnt++;
			comboCurrTime = 0;
			UE_LOG(LogTemp, Warning, TEXT("%d타"), comboCnt);

			playAnimation = true;
			sectionName = TEXT("Attack2");

			//플레이어 이동 정지
			GetCharacterMovement()->SetMovementMode(MOVE_None);
			//공격하고 있을 때 점프 막자
			

		}
	}

	//만약 콤보 카운트가 3 미만일 때 
	else if (comboCnt == 2)
	{
		// 만약 콤보현재시간이 최소시간보다 작거나 같고 and 최대시간이 작거나 같을 때
		if (comboMinTime <= comboCurrTime && comboCurrTime <= comboMaxTime)
		{
			// 콤보 카운트 1 증가시키고 현재시간 0 으로 초기화 
			comboCnt++;
			comboCurrTime = 0;
			UE_LOG(LogTemp, Warning, TEXT("%d번째 공격 모션"), comboCnt);

			playAnimation = true;
			sectionName = TEXT("Attack3");

			//플레이어 이동 정지
			GetCharacterMovement()->SetMovementMode(MOVE_None);
			

		}
	}

	// 나 애니메이션 플레이 해야 하니?
	if (playAnimation == true)
	{
		// AnimInstance를 가져오기
		auto AnimInstance = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
		//FString sectionName = FString::Printf(TEXT("Atttack%d"), comboCnt);
		AnimInstance->ComboAttackMontage(sectionName);
	}
}


void ACppPlayer::UpdateCombo(float deltaTime)
{
	// 콤보 카운트가 0보다 크면 (콤보 시작)
	if (comboCnt > 0)
	{
		//콤보 현재시간 = 콤보 현재시간 + 델타타임 -> 콤보 현재시간을 증가시켜라
		comboCurrTime += deltaTime;
		//콤보 현재 시간이 최대시간보다 커졌을 때
		if (comboCurrTime > comboMaxTime)
		{
			// 콤보 카운트를 초기화 시켜라 -> 콤보 처음부터 시작하기 위해서
			comboCnt = 0;

			// 움직임, 점프 활성화
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			GetCharacterMovement()->SetJumpAllowed(true);

			
		}
	}
}


