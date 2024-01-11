// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFSM.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CppPlayer.h"
#include "DarkSoules_Boss_Fight.h"

// Sets default values for this component's properties
UBossFSM::UBossFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBossFSM::BeginPlay()
{
	Super::BeginPlay();

	AActor* findActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACppPlayer::StaticClass());
	target = Cast<ACppPlayer>(findActor);

	myActor = Cast<ADarkSoules_Boss_Fight>(GetOwner());
	
}


// Called every frame
void UBossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (target == nullptr) return;

	switch (currState)
	{
	case EEnemyState::IDLE:
		UpdateIdle();
		break;
	case EEnemyState::MOVE:
		UpdateMove();
		break;
	case EEnemyState::ATTACK:
		UpdateAttack();
		break;

	default:
		break;
	}
}

void UBossFSM::ChangeState(EEnemyState s)
{
	currState = s;

	switch (currState)
	{
	case EEnemyState::IDLE:
		break;
	case EEnemyState::MOVE:
		break;
	case EEnemyState::ATTACK:
		currTime = attackDelayTime;
		break;
	default:
		break;
	}
}

void UBossFSM::UpdateIdle()
{
	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	float dist = dir.Length();
	if (dist < traceRange) {
		ChangeState(EEnemyState::MOVE);
	}
}

void UBossFSM::UpdateMove()
{
	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	myActor->AddMovementInput(dir.GetSafeNormal());
	float dist = dir.Length();
	if (dist < attackRange) {
		ChangeState(EEnemyState::ATTACK);
	}

}

void UBossFSM::UpdateAttack()
{
	currTime += GetWorld()->GetDeltaSeconds();

	if (currTime > attackDelayTime) {
		float dist = FVector::Distance(target->GetActorLocation(), myActor->GetActorLocation());

		if (dist < attackRange) {

		}
		else if (dist < traceRange) {
			ChangeState(EEnemyState::MOVE);
		}
		else ChangeState(EEnemyState::IDLE);
	}
	currTime = 0;
}

