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
	// ������ ����
	UPlayerAnim();
	
public:
	//�÷��̾� �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	float speed = 0;

	//�÷��̾� ���ִ°�?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	bool bIsIdle = 1;
	
	//�÷��̾� ���������ΰ�?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	bool bIsJuming = 1;
	
	//�÷��̾� ���������ֳ�?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerVariables)
	bool bIsFalling = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
	TObjectPtr<class UCharacterMovementComponent> Movement;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
	float MovingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerVariables)
	float JumpingThreshold;

	//�޺� ���� ��Ÿ�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack)
	UAnimMontage* AttackMontage;

public:
	

	//�� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//�ִϸ��̼� �ʱ�ȭ
	virtual void NativeInitializeAnimation() override;

	//���� ��Ÿ�� �Լ� ����
	void ComboAttackMontage(FName sectionName);

};
