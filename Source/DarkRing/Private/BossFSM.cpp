// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFSM.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CppPlayer.h"
#include "DarkSoules_Boss_Fight.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "BossAnim2.h"
#include "EnergySphere.h"

// Sets default values for this component's properties
UBossFSM::UBossFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UAnimMontage> tempMontage(TEXT("/Script/Engine.AnimMontage'/Game/KEJ/EJBluePrints/BossMontage.BossMontage'"));
	if (tempMontage.Succeeded()) {
		montage = tempMontage.Object;
	}
	ConstructorHelpers::FClassFinder<AEnergySphere> tempESphere(TEXT("/Script/Engine.Blueprint'/Game/KEJ/EJBluePrints/BP_Energy_Sphere.BP_Energy_Sphere_C'"));
	if (tempESphere.Succeeded()) {
		energySphere = tempESphere.Class;
	}

}


// Called when the game starts
void UBossFSM::BeginPlay()
{
	Super::BeginPlay();

	AActor* findActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACppPlayer::StaticClass());
	target = Cast<ACppPlayer>(findActor);

	myActor = Cast<ADarkSoules_Boss_Fight>(GetOwner());
	
	
	USkeletalMeshComponent* mesh = myActor->GetMesh();
	UAnimInstance* animInstance = mesh->GetAnimInstance();
	anim = Cast<UBossAnim2>(animInstance);

	originPos = myActor->GetActorLocation();
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
	case EEnemyState::DAMAGE:
		UpdateDamaged();
	case EEnemyState::BOMB:
		UpdateBomb();
		break;
	case EEnemyState::DASH:
		UpdateDash();
		break;
	case EEnemyState::RETURN:
		UpdateReturn();
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
	anim->state = currState;

	currTime = 0;
	switch (currState)
	{
	case EEnemyState::IDLE:
		break;
	case EEnemyState::MOVE:
		break;
	case EEnemyState::ATTACK: {
		currTime = attackDelayTime;
		int32 rand = FMath::RandRange(0, 1);
		anim->attackType = (EAttackType)rand;
	}
		break;
	case EEnemyState::DAMAGE: {
		int32 rand = FMath::RandRange(1, 2);
		FString sectionName = FString::Printf(TEXT("Damage0%d"), rand);
		myActor->PlayAnimMontage(montage, 1.0f, FName(sectionName));
	}
		break;
	case EEnemyState::BOMB:

		makeSphere = true;
		dashCurrTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("bomb"));
		//attackCount = 0;
		break;
	case EEnemyState::DASH:
	{
		dashCurrTime = 0;
		dashDir = target->GetActorLocation() - myActor->GetActorLocation();
	}
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
	myActor->GetCharacterMovement()->MaxWalkSpeed = 300;

	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	myActor->AddMovementInput(dir.GetSafeNormal());
	float dist = dir.Length();
	//UE_LOG(LogTemp, Warning, TEXT("%f"), dist);
	if (dist < attackRange) {
		ChangeState(EEnemyState::ATTACK);
	}
	else if (dist > traceRange) {
		ChangeState(EEnemyState::RETURN);
	}
	else
	{
		return;
	}

}

void UBossFSM::UpdateAttack()
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), currTime);

	dashCurrTime += GetWorld()->DeltaTimeSeconds;


	float dist = FVector::Distance(target->GetActorLocation(), myActor->GetActorLocation());

	if (dist < attackRange)
	{
		//attackCount++;

		if (IsWaitComplete(attackDelayTime))
		{
			//UE_LOG(LogTemp, Warning, TEXT("attack"));


			if (dashCurrTime > dashDelayTime)
			{
				UE_LOG(LogTemp, Warning, TEXT("run"));
				ChangeState(EEnemyState::BOMB);
			}
		}
	}

	else if (dist < traceRange)
	{
		//dashCurrTime = 0;

		ChangeState(EEnemyState::MOVE);
	}
	else
	{
		//dashCurrTime = 0;

		//UE_LOG(LogTemp, Warning, TEXT("reIdle"));
		ChangeState(EEnemyState::IDLE);
	}


}




void UBossFSM::UPdateAttackDelay()
{

}

void UBossFSM::UpdateDamaged()
{
	if (IsWaitComplete(damageDelayTime)) {
		ChangeState(EEnemyState::IDLE);
	}
}


void UBossFSM::UpdateBomb()
{

if (IsWaitComplete(bombReadyTime)) {
		//주위에 강한데미지

		UE_LOG(LogTemp, Warning, TEXT("bomb ing"));

// 		currTime = 0;
// 		if (IsWaitComplete(3)) {
 			ChangeState(EEnemyState::DASH);
			//SpawnedActorRef->Destroy();

//		}
 	}
 	else {
 		//모션 상태로 멈춰있음
		//UE_LOG(LogTemp, Warning, TEXT("ANIM"));

		//UGameplayStatics::SpawnObject(energySphere,)


		if (makeSphere) {
			//FActorSpawnParameters SpawnParams;
			for (int i = 0; i < 5; i++){
				//SpawnedActorRef = 
				GetWorld()->SpawnActor<AEnergySphere>(energySphere, myActor->GetActorLocation(), myActor->GetActorRotation());

			}

			makeSphere = false;

		}
 	}

}

void UBossFSM::UpdateDash()
{
	//바로 Dash		
		myActor->GetCharacterMovement()->MaxWalkSpeed = 3500;

		myActor->AddMovementInput(dashDir);

		float dist = FVector::Distance(myActor->GetActorLocation(), target->GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("%f"), dist);

		if (IsWaitComplete(1.5) || dist < 250) {
			ChangeState(EEnemyState::IDLE);
		}


}

bool UBossFSM::IsWaitComplete(float delay)
{
	currTime += GetWorld()->DeltaTimeSeconds;
	if (currTime >= delay) {
		return true;
	}
	return false;

}

void UBossFSM::UpdateReturn()
{

	FVector dir = originPos - myActor->GetActorLocation();

	myActor->AddMovementInput(dir);

	float dist = FVector::Distance(originPos, myActor->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("%f"), dist);
	if (dist < 50) {

		ChangeState(EEnemyState::IDLE);
	}
}

