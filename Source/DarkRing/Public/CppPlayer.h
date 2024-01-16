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

	//콤보 카운트와 콤보 타이밍 시간 변수
	int32 comboCnt = 0;
	float comboMinTime = 0.5f;
	float comboMaxTime = 0.8f;
	float comboCurrTime = 0;


	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackMontage;

public:

	void MoveAction(FVector2d keyboardInput);

	void InputHorizontal(float value);
	void InputVertical(float value);
	
	void EnhancedJump();
	void EnhancedMouse(const struct FInputActionValue& value);
	void EnhancedMove(const struct FInputActionValue& value);

	void EnhancedAttck(const struct FInputActionValue& value);

	void UpdateCombo(float deltaTime);

	///-------------------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* sceneAttack;

	

	
	
};
