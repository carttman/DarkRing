// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "CppPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

UPlayerAnim::UPlayerAnim()
{
	// Combo Attack 몽타주를 파일 읽어오자
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMCA(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Combo_Attack.AM_Combo_Attack'"));
	if (AMCA.Succeeded()) //가져오기 성공시 
	{
			// 선언한 AttackMontage 변수에 object 전달
			AttackMontage = AMCA.Object;
	}

	// Rolling 몽타주 파일 읽어오자
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMR(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Rolling.AM_Rolling'"));
	if (AMR.Succeeded())
	{
		// 선언한 RollingMontage 변수에 object 전달
		RollingMontage = AMR.Object;
	}

	//AbilityQ 몽타주를 파일 읽어오자
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMAQ(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_AbilityQ.AM_AbilityQ'"));
	if (AMAQ.Succeeded()) //가져오기 성공시 
	{
		// 선언한 AttackMontage 변수에 object 전달
		AbilityQMontage = AMAQ.Object;
	}

	//AbilityE 몽타주를 파일 읽어오자
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMAE(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_AbilityE.AM_AbilityE'"));
	if (AMAQ.Succeeded()) //가져오기 성공시 
	{
		// 선언한 AttackMontage 변수에 object 전달
		AbilityEMontage = AMAE.Object;
	}

	//AbilityR 몽타주를 파일 읽어오자
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMAR(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_AbilityR.AM_AbilityR'"));
	if (AMAR.Succeeded()) //가져오기 성공시 
	{
		// 선언한 AttackMontage 변수에 object 전달
		AbilityRMontage = AMAR.Object;
	}

	//ConstructorHelpers::FClassFinder<ASpawnEIce> tempSEI(TEXT("/Script/Engine.Blueprint'/Game/BlueprintBP_SpawnEIce.BP_SpawnEIce_C'"));
	//if (tempSEI.Succeeded())
	//{
	//	IceFactory = tempSEI.Class;
	//}
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//플레이어의 이동 속도를 가져와 speed 에 할당하고 싶다
	//1. 소유 폰 얻어오기
	auto ownerPawn = TryGetPawnOwner();

	//2. 플레이어로 캐스팅하기
	auto player = Cast<ACppPlayer>(ownerPawn);

	//캐스팅에 성공했을 때 
	if (player)
	{
		//3. 이동속도가 필요
		FVector Velocity = player->GetVelocity();

		//4. 플레이어의 전방 벡터가 필요
		FVector forwardVector = player->GetActorForwardVector();

		//5. speed에 값(내적) 할당하기
		speed = FVector::DotProduct(forwardVector, Velocity);

		// 플레이어가 현재 공중에 있는지 여부를 기억하고 싶다.
		auto movement = player->GetCharacterMovement();
		IsInAir = movement->IsFalling();
	}
	
}

void UPlayerAnim::NativeInitializeAnimation()
{

}

// ComboAttack 몽타주 함수 (FName 가져올 섹션이름)
void UPlayerAnim::ComboAttackMontage(FName sectionName)
{
	// 몽타주 실행(몽타주 파일 담은 변수, 플레이 시간)
	Montage_Play(AttackMontage, 1.f);
	
	
	// 몽타주 섹션 점프(섹션 이름, 몽타주 파일 담은 변수)
	Montage_JumpToSection(sectionName, AttackMontage);
}

void UPlayerAnim::RollingDodgeMontage(FName sectionName)
{
	// 몽타주 실행(몽타주 파일 담은 변수, 플레이 시간)
	Montage_Play(RollingMontage, 1.f);

	// 몽타주 섹션 점프
	Montage_JumpToSection(sectionName, RollingMontage);

}

void UPlayerAnim::SkillQMontage(FName sectionName)
{
	// 몽타주 실행(몽타주 파일 담은 변수, 플레이 시간)
	Montage_Play(AbilityQMontage, 1.f);

	// 몽타주 섹션 점프
	Montage_JumpToSection(sectionName, AbilityQMontage);
}

void UPlayerAnim::SkillEMontage(FName sectionName)
{
	// 몽타주 실행(몽타주 파일 담은 변수, 플레이 시간)
	Montage_Play(AbilityEMontage, 1.f);

	// 몽타주 섹션 점프
	Montage_JumpToSection(sectionName, AbilityEMontage);
}

void UPlayerAnim::SkillRMontage(FName sectionName)
{
	// 몽타주 실행(몽타주 파일 담은 변수, 플레이 시간)
	Montage_Play(AbilityRMontage, 1.f);

	// 몽타주 섹션 점프
	Montage_JumpToSection(sectionName, AbilityRMontage);
}

void UPlayerAnim::AnimNotify_ThrowIce()
{	
	//1. cpp player 캐스팅하자
	APawn* player = TryGetPawnOwner();
	ACppPlayer* myPlayer = Cast<ACppPlayer>(player);

	// cpp player에 있는 E스킬 함수 가져와
	myPlayer->UpdateESkill();
}

