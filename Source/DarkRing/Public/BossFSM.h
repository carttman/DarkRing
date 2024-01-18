// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE,
	MOVE,
	ATTACK,
	ATTACK_DELAY,
	DAMAGE,
	BOMB,
	DASH
};

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	RIGHT,
	LEFT
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKRING_API UBossFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	EEnemyState currState = EEnemyState::IDLE;

	UPROPERTY(EditAnywhere)
	class ACppPlayer* target;
	UPROPERTY(EditAnywhere)
	class ADarkSoules_Boss_Fight* myActor;

	UPROPERTY(EditAnywhere)
	class UBossAnim2* anim;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* montage;

	UPROPERTY(EditAnywhere)
	float traceRange = 1000;
	UPROPERTY(EditAnywhere)
	float attackRange = 200;

	UPROPERTY(EditAnywhere)
	float currTime = 0;
	UPROPERTY(EditAnywhere)
	float attackDelayTime = 1;
	float damageDelayTime = 2;

// 	UPROPERTY(EditAnywhere)
// 	int attackCount = 0;

	UPROPERTY(EditAnywhere)
	float dashCurrTime = 0;
	float dashDelayTime = 3;

	//�÷��̾� ������ �ð�
	UPROPERTY(EditAnywhere)
	float bombReadyTime = 5; 

	UPROPERTY(EditAnywhere)
	FVector dashDir;

public:
	void ChangeState(EEnemyState s);
	void UpdateIdle();
	void UpdateMove();
	void UpdateAttack();
	void UPdateAttackDelay();

	void UpdateDamaged();

	void UpdateBomb();
	void UpdateDash();

	bool IsWaitComplete(float delay);


};
