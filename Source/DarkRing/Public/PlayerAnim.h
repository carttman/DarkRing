// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"


/**
 * 
 */
UCLASS()
class DARKRING_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// 생성자 선언
	UPlayerAnim();
	
public:
	//플레이어 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	float speed = 0;
	
	//플레이어 점프상태인가?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerVariables)
	bool IsInAir = false;
	
	//콤보 공격 몽타주 변수 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack)
	UAnimMontage* AttackMontage;

	//구르기 몽타주 변수 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rolling)
	UAnimMontage* RollingMontage;

public:
	

	//매 프레임 갱신되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//애니메이션 초기화
	virtual void NativeInitializeAnimation() override;

	//공격 몽타주 함수 선언
	void ComboAttackMontage(FName sectionName);
	//구르기 몽타주 함수 선언
	void RollingDodgeMontage(FName sectionName);

};
