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

	//플레이어 서있는가?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	bool bIsIdle = 1;
	
	//플레이어 점프상태인가?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	bool bIsJuming = 1;
	
	//플레이어 떨어지고있나?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	bool bIsFalling = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
	TObjectPtr<class UCharacterMovementComponent> Movement;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
	float MovingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
	float JumpingThreshold;

	//콤보 공격 몽타주 변수 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack)
	UAnimMontage* AttackMontage;

public:
	

	//매 프레임 갱신되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//애니메이션 초기화
	virtual void NativeInitializeAnimation() override;

	//공격 몽타주 함수 선언
	void ComboAttackMontage(FName sectionName);

};
