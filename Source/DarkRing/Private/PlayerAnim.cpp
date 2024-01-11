// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "CppPlayer.h"

UPlayerAnim::UPlayerAnim()
{
	// Combo Attack 몽타주를 파일 읽어오자
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Combo_Attack.AM_Combo_Attack'"));
	if (AM.Succeeded()) //가져오기 성공시 
	{
			// 선언한 AttackMontage 변수에 object 전달
			AttackMontage = AM.Object;
	}
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




