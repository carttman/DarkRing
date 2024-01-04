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

	float moveSpeed = 500;

	// È¸Àü °ª
	float mx = 0;
	float my = 0;

public:

	void MoveAction();
	void RotateAction();

	void InputHorizontal(float value);
	void InputVertical(float value);
	void InputMouseX(float value);
	void InputMouseY(float value);
	void InputJump();
};
