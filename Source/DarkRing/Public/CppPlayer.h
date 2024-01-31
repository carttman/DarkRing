// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h>
#include "CppPlayer.generated.h"

UCLASS()
class DARKRING_API ACppPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACppPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArm;
	
	// UPROPERTY(EditAnywhere)
	// ECollisionChannel springColl = ECC_Visibility;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;

	// float h; , float v;
	FVector moveInput = FVector(0);

	float moveSpeed = 500;


	// Input Mapping Context 담을 변수
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* imcDefault;

	// InputAction Jump
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_Jump;

	// InputAction Mouse
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_MouseMove;

	//InputAction Move (W, A, S, D)
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_Move;

	//InputAction Attack
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_Attack;

	//InputAction Rolling
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_Rolling;

	//InputAction AbilityQ
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_AbilityQ;
	
	//InputAction AbilityE
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_AbilityE;

	//InputAction AbilityR
	UPROPERTY(EditAnywhere)
	class UInputAction* ia_AbilityR;

	//
	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* sword;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpawnEIce> IceFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASpawnSwordAura> ultSwordFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf <class UAnimInstance> abpClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* ultAura;
	//spawn E Ice
	UPROPERTY(EditAnywhere)
	class AActor* spawnEIce;

	//콤보 카운트와 콤보 타이밍 시간 변수
	int32 comboCnt = 0;
	float comboMinTime = 0.5f;
	float comboMaxTime = 0.8f;
	float comboCurrTime = 0;
	bool isAttacking = false;

	float nowRollingTime = 0;
	float maxRollingTime = 0.5f;
	FVector rollingDir = FVector(0);
	
	// 구르기를 할 수 있는가?
	bool isRolling = false;
	// 구르기 중인가??
	bool whileRolling = false;
	//구르기 속도
	float rollingSpeed = 1200;

	
	float skillEMinTime = 0;
	float skillEMaxTime = 1.f;
	float skillECurrTime = 0;

	//궁극기 사용 중인가?
	bool isUltimaiting = false;
	//궁 캐스팅 하는 중?
	bool whileUlt = false;
	//궁 검기 던져
	bool isthrowUlt = false;

	bool isUltAuraOn = false;
	//궁극 버프 지속시간
	float currUltTime = 0;
	float minUltTime = 0;
	float maxUltTime = 20;



	bool isCastingE = false;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* RollingMontage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AbilityQMontage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AbilityEMontage;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AbilityRMontage;
public:

	void MoveAction(FVector2d keyboardInput);
	void InputHorizontal(float value);
	void InputVertical(float value);
	
	void EnhancedJump();
	void EnhancedMouse(const struct FInputActionValue& value);
	void EnhancedMove(const struct FInputActionValue& value);

	void EnhancedAttck(const struct FInputActionValue& value);
	void EnhancedRolling(const struct FInputActionValue& value);
	void EnhancedAbilityQ(const struct FInputActionValue& value);
	void EnhancedAbilityE(const struct FInputActionValue& value);
	void EnhancedAbilityR(const struct FInputActionValue& value);

	void UpdateCombo(float deltaTime);
	void UpdateRolling(float deltaTime);
	void UpdateESkill();

	void UpdateUlt(float deltaTime);
	
	///-------------------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* sceneAttack;

	

	
	
};
