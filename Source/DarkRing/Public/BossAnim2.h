// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossFSM.h"
#include "BossAnim2.generated.h"

/**
 * 
 */
UCLASS()
class DARKRING_API UBossAnim2 : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyState state;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType attackType;
};
