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
	
	//�÷��̾� ���������ΰ�?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerVariables)
	bool IsInAir = false;
	
	//�޺� ���� ��Ÿ�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboAttack)
	UAnimMontage* AttackMontage;

	//������ ��Ÿ�� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rolling)
	UAnimMontage* RollingMontage;

public:
	

	//�� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//�ִϸ��̼� �ʱ�ȭ
	virtual void NativeInitializeAnimation() override;

	//���� ��Ÿ�� �Լ� ����
	void ComboAttackMontage(FName sectionName);
	//������ ��Ÿ�� �Լ� ����
	void RollingDodgeMontage(FName sectionName);

};
