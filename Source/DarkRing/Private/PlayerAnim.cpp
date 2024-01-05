// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "CppPlayer.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//플레이어의 이동 속도를 가져와 speed에 할당하고 싶다
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
		UE_LOG(LogTemp, Warning, TEXT("%f"), speed);

	}
}
