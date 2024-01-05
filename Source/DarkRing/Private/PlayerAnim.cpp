// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "CppPlayer.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//�÷��̾��� �̵� �ӵ��� ������ speed�� �Ҵ��ϰ� �ʹ�
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
		UE_LOG(LogTemp, Warning, TEXT("%f"), speed);

	}
}
