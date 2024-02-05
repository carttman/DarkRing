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

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;

	// float h; , float v;
	FVector moveInput = FVector(0);

	// �̵��ӵ�
	float moveSpeed = 500;

public: // Enhanced input ������
	
	// Input Mapping Context ���� ����
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

public: // ��ų�� ���� ���� ���Ϳ� �ִϸ��̼� Ŭ���� 
	
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

	UPROPERTY(EditAnywhere)
	class AActor* spawnEIce;

	//�޺� ī��Ʈ�� �޺� Ÿ�̹� �ð� ����
	int32 comboCnt = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float comboMinTime = 0.5f;
	float comboMaxTime = 0.8f;
	float comboCurrTime = 0;
	// �������ΰ�?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAttacking = false;

	//���� ������ �ð��� ����ϴ� ������ ������ �Ÿ� ����
	float nowRollingTime = 0;
	float maxRollingTime = 0.5f;
	FVector rollingDir = FVector(0);
	
	// �����⸦ �� �� �ִ°�?
	bool isRolling = false;
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool whileRolling = false;
	//������ �ӵ�
	float rollingSpeed = 1200;

	
	float skillEMinTime = 0;
	float skillEMaxTime = 1.f;
	float skillECurrTime = 0;

	//�ñر� ��� ���ΰ�?
	bool isUltimaiting = false;
	//�� ĳ���� �ϴ� ��?
	bool whileUlt = false;
	//�� �˱� ����
	bool isthrowUlt = false;

	bool isUltAuraOn = false;
	//�ñ� ���� ���ӽð�
	float currUltTime = 0;
	float minUltTime = 0;
	float maxUltTime = 20;

	bool isCastingE = false;

	// MP ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxMP = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currMP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minMP = 0;

	// Stemina ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxStemina = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currStemina = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minStemina = 0;

public: // ��Ÿ�� Ŭ������

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
	
	void UpdateMP(float deltaTime);

	void UpdateStemina(float deltaTime);
	///-------------------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* sceneAttack;

	

	
	
};
