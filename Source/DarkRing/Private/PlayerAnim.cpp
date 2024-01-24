// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "CppPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

UPlayerAnim::UPlayerAnim()
{
	// Combo Attack ��Ÿ�ָ� ���� �о����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMCA(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Combo_Attack.AM_Combo_Attack'"));
	if (AMCA.Succeeded()) //�������� ������ 
	{
			// ������ AttackMontage ������ object ����
			AttackMontage = AMCA.Object;
	}

	// Rolling ��Ÿ�� ���� �о����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMR(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Rolling.AM_Rolling'"));
	if (AMR.Succeeded())
	{
		// ������ RollingMontage ������ object ����
		RollingMontage = AMR.Object;
	}

	//AbilityQ ��Ÿ�ָ� ���� �о����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMAQ(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_AbilityQ.AM_AbilityQ'"));
	if (AMAQ.Succeeded()) //�������� ������ 
	{
		// ������ AttackMontage ������ object ����
		AbilityQMontage = AMAQ.Object;
	}

	//AbilityE ��Ÿ�ָ� ���� �о����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMAE(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_AbilityE.AM_AbilityE'"));
	if (AMAQ.Succeeded()) //�������� ������ 
	{
		// ������ AttackMontage ������ object ����
		AbilityEMontage = AMAE.Object;
	}

	//AbilityR ��Ÿ�ָ� ���� �о����
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMAR(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_AbilityR.AM_AbilityR'"));
	if (AMAR.Succeeded()) //�������� ������ 
	{
		// ������ AttackMontage ������ object ����
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

	//�÷��̾��� �̵� �ӵ��� ������ speed �� �Ҵ��ϰ� �ʹ�
	//1. ���� �� ������
	auto ownerPawn = TryGetPawnOwner();

	//2. �÷��̾�� ĳ�����ϱ�
	auto player = Cast<ACppPlayer>(ownerPawn);

	//ĳ���ÿ� �������� �� 
	if (player)
	{
		//3. �̵��ӵ��� �ʿ�
		FVector Velocity = player->GetVelocity();

		//4. �÷��̾��� ���� ���Ͱ� �ʿ�
		FVector forwardVector = player->GetActorForwardVector();

		//5. speed�� ��(����) �Ҵ��ϱ�
		speed = FVector::DotProduct(forwardVector, Velocity);

		// �÷��̾ ���� ���߿� �ִ��� ���θ� ����ϰ� �ʹ�.
		auto movement = player->GetCharacterMovement();
		IsInAir = movement->IsFalling();
	}
	
}

void UPlayerAnim::NativeInitializeAnimation()
{

}

// ComboAttack ��Ÿ�� �Լ� (FName ������ �����̸�)
void UPlayerAnim::ComboAttackMontage(FName sectionName)
{
	// ��Ÿ�� ����(��Ÿ�� ���� ���� ����, �÷��� �ð�)
	Montage_Play(AttackMontage, 1.f);
	
	
	// ��Ÿ�� ���� ����(���� �̸�, ��Ÿ�� ���� ���� ����)
	Montage_JumpToSection(sectionName, AttackMontage);
}

void UPlayerAnim::RollingDodgeMontage(FName sectionName)
{
	// ��Ÿ�� ����(��Ÿ�� ���� ���� ����, �÷��� �ð�)
	Montage_Play(RollingMontage, 1.f);

	// ��Ÿ�� ���� ����
	Montage_JumpToSection(sectionName, RollingMontage);

}

void UPlayerAnim::SkillQMontage(FName sectionName)
{
	// ��Ÿ�� ����(��Ÿ�� ���� ���� ����, �÷��� �ð�)
	Montage_Play(AbilityQMontage, 1.f);

	// ��Ÿ�� ���� ����
	Montage_JumpToSection(sectionName, AbilityQMontage);
}

void UPlayerAnim::SkillEMontage(FName sectionName)
{
	// ��Ÿ�� ����(��Ÿ�� ���� ���� ����, �÷��� �ð�)
	Montage_Play(AbilityEMontage, 1.f);

	// ��Ÿ�� ���� ����
	Montage_JumpToSection(sectionName, AbilityEMontage);
}

void UPlayerAnim::SkillRMontage(FName sectionName)
{
	// ��Ÿ�� ����(��Ÿ�� ���� ���� ����, �÷��� �ð�)
	Montage_Play(AbilityRMontage, 1.f);

	// ��Ÿ�� ���� ����
	Montage_JumpToSection(sectionName, AbilityRMontage);
}

void UPlayerAnim::AnimNotify_ThrowIce()
{	
	//1. cpp player ĳ��������
	APawn* player = TryGetPawnOwner();
	ACppPlayer* myPlayer = Cast<ACppPlayer>(player);

	// cpp player�� �ִ� E��ų �Լ� ������
	myPlayer->UpdateESkill();
}

