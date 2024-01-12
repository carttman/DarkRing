// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFSM.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CppPlayer.h"
#include "DarkSoules_Boss_Fight.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

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
		UpdateAttack(DeltaTime);
		break;
	case EEnemyState::DASH:
		UpdateDash();
		break;

	default:
		break;
	}
}

void UBossFSM::ChangeState(EEnemyState s)
{
	UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEnemyState"), true);
	if (enumPtr != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s-------> %s"), *enumPtr->GetNameStringByIndex((int32)currState), *enumPtr->GetNameStringByIndex((int32)s));
	}

	currState = s;

	currTime = 0;
	switch (currState)
	{
	case EEnemyState::IDLE:
		break;
	case EEnemyState::MOVE:
		break;
	case EEnemyState::ATTACK:
		currTime = attackDelayTime;
		break;
	case EEnemyState::DASH:
		dashCurrTime = 0;
	default:
		break;
	}
}

void UBossFSM::UpdateIdle()
{
	myActor->GetCharacterMovement()->MaxWalkSpeed = 300;

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
	//UE_LOG(LogTemp, Warning, TEXT("%f"), dist);
	if (dist < attackRange) {
		ChangeState(EEnemyState::ATTACK);
	}

}

void UBossFSM::UpdateAttack(float deltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), currTime);
	
	
	currTime += deltaTime;

	/*
	if (currTime > attackDelayTime) {
		float dist = FVector::Distance(target->GetActorLocation(), myActor->GetActorLocation());

		if (dist < attackRange) {
			UE_LOG(LogTemp, Warning, TEXT("attack"));

		}
		else if (dist < traceRange) {
			ChangeState(EEnemyState::MOVE);
		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("reIdle"));
			ChangeState(EEnemyState::IDLE);
		}
		currTime = 0;
	}
	*/

	if (currTime > bombCoolTime) {
		//주위에 강한데미지
		UE_LOG(LogTemp, Warning, TEXT("bomb"));
		ChangeState(EEnemyState::DASH);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("attack"));

	}

}

void UBossFSM::UpdateDamaged(float deltaTime)
{
	currTime += deltaTime;
	if (currTime > damageDelayTime) {
		ChangeState(EEnemyState::IDLE);
	}
}

void UBossFSM::UpdateDash()
{
	currTime += GetWorld()->GetDeltaSeconds();
	if (currTime > dashDelayTime)
	{
		FVector dir = target->GetActorLocation() - myActor->GetActorLocation();

		myActor->GetCharacterMovement()->MaxWalkSpeed = 1000;

		//FVector through = dir.GetSafeNormal() 
		myActor->AddMovementInput(dir.GetSafeNormal() + FVector(300));

		if (dir.Length() < 130) {
			ChangeState(EEnemyState::IDLE);

		}
	}
	
}

void UBossFSM::UpdateBomb()
{

}

