// Fill out your copyright notice in the Description page of Project Settings.


#include "BossFSM.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CppPlayer.h"
#include "DarkSoules_Boss_Fight.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "BossAnim2.h"
#include "EnergySphere.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>


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

	//UE_LOG(LogTemp, Warning, TEXT("currTime2 : %f, 2 : %f"), currTime, currTime2);

	if(start && IsWaitComplete(3)) ChangeState(EEnemyState::RETURN);

	if(IsWaitComplete2(10) && makeSphere == 0) SphereFactory();

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
	case EEnemyState::ATTACK_DELAY:
		UPdateAttackDelay();
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
		myActor->GetCharacterMovement()->MaxWalkSpeed = 300;
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
	case EEnemyState::ATTACK_DELAY:

		break;
	case EEnemyState::BOMB:
		currTime2 =0;
		makeSphere = 0;
		dashCurrTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("bomb"));
		//attackCount = 0;
		break;
	case EEnemyState::DASH:
	{
		dashCurrTime = 0;
		dashDir = target->GetActorLocation() - myActor->GetActorLocation();
		targetDash = UKismetMathLibrary::RandomBool();

	}
	default:
	case EEnemyState::RETURN:
	{
		targetPos = target->GetActorLocation();
	}

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

	makeSphere = 0;

	float dist = FVector::Distance(target->GetActorLocation(), myActor->GetActorLocation());

	if (dist < attackRange)
	{
		Looking();
		
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
	if (IsWaitComplete(3)) {
		ChangeState(EEnemyState::MOVE);

	}

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
		//������ ���ѵ�����

		//UE_LOG(LogTemp, Warning, TEXT("bomb ing"));

		// 		currTime = 0;
		// 		if (IsWaitComplete(3)) {
		ChangeState(EEnemyState::DASH);
		//SpawnedActorRef->Destroy();

//		}
	}
	else if (currTime > 1) {
		//��� ���·� ��������
		//UE_LOG(LogTemp, Warning, TEXT("ANIM"));

		//UGameplayStatics::SpawnObject(energySphere,)

		Looking();

			if (makeSphere == 0) {
				//FActorSpawnParameters SpawnParams;
				//int32 degree = 10;

				SphereFactory();
				
				//UE_LOG(LogTemp, Warning, TEXT("i is"));
		
			}
			else if(makeSphere == 1 && currTime > 2) SphereFactory();
			else if(makeSphere == 2 && currTime > 3) SphereFactory();


	}
	else Looking();

}

void UBossFSM::UpdateDash()
{

	//�ٷ� Dash		
		myActor->GetCharacterMovement()->MaxWalkSpeed = 3500;
		
		float dist = FVector::Distance(myActor->GetActorLocation(), target->GetActorLocation());

		if (targetDash) {
			UE_LOG(LogTemp, Warning, TEXT("dash optional"));

			myActor->AddMovementInput(dashDir);
			
			if (IsWaitComplete(1.5) || dist < 150) {
				ChangeState(EEnemyState::ATTACK_DELAY);
			}

		}
		//������ dash Ÿ��
		else {
			UE_LOG(LogTemp,Warning,TEXT("dash must attack"));
			myActor->AddMovementInput(target->GetActorLocation()- myActor->GetActorLocation());
			if (dist < 150) {
				ChangeState(EEnemyState::ATTACK_DELAY);
			}

		}


		//UE_LOG(LogTemp, Warning, TEXT("%f"), dist);



}

bool UBossFSM::IsWaitComplete(float delay)
{
	currTime += GetWorld()->DeltaTimeSeconds;
	if (currTime >= delay) {
		return true;
	}
	return false;

}
bool UBossFSM::IsWaitComplete2(float delay)
{
	currTime2 += GetWorld()->DeltaTimeSeconds;
	if (currTime2 >= delay) {
		return true;
	}
	return false;

}

//�����̵����� �ٲ�
void UBossFSM::UpdateReturn()
{
	start = false;

	myActor->SetActorLocation(targetPos + (target->GetActorForwardVector() + FVector(70)));

	if(IsWaitComplete(1)) ChangeState(EEnemyState::MOVE);

	//FVector dir = originPos - myActor->GetActorLocation();

	//FVector distacnePtoB = myActor->GetActorLocation() - target->GetActorLocation();

	/*myActor->AddMovementInput(dir);

	if (distacnePtoB.Length() < attackRange) ChangeState(EEnemyState::ATTACK);
	else if(distacnePtoB.Length() < traceRange) ChangeState(EEnemyState::MOVE);
	else {

		float dist = FVector::Distance(originPos, myActor->GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT("%f"), dist);
		if (dist < 50) {

			ChangeState(EEnemyState::IDLE);
		}

	}
	*/
}

void UBossFSM::Looking()
{
	FVector dir = target->GetActorLocation() - myActor->GetActorLocation();
	FRotator rot = UKismetMathLibrary::MakeRotFromXZ(dir, myActor->GetActorUpVector());

	myActor->SetActorRelativeRotation(rot);

}

void UBossFSM::SphereFactory()
{
	float sphereAttackTime = FMath::RandRange(0.5f, 2.0f);

	currTime2 = 0;

	FVector pos;
	float halfValue = ((sphereCnt - 1) * 100) / 2.0f;

	float roll = 0;
	float angle = 360.0f / sphereCnt;



		for (int32 i = 0; i < sphereCnt; i++) {
			

			pos = myActor->GetActorLocation();

			roll = i * angle;

			//UKismetMathLibrary::MakeRotFromXZ(pos)

			//FVector dir = (target->GetActorLocation() + target->GetActorRightVector() * i * 200) - myActor->GetActorLocation();

			GetWorld()->SpawnActor<AEnergySphere>(energySphere, pos, FRotator(0, roll, 0));

			//myActor->GetActorLocation() + FVector(myActor->GetActorRightVector() * i * 100)

		}

	makeSphere++;

}

