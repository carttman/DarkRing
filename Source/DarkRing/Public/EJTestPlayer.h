// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EJTestPlayer.generated.h"

UCLASS()
class DARKRING_API AEJTestPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEJTestPlayer();

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
	class USpringArmComponent* arm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* cam;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* imcDafault;

	UPROPERTY(EditAnywhere)
	class UInputAction* ia_MouseMove;


// 
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
// 	UInputAction* inputToJump;
// 
// 
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
// 	UInputAction* inputToMove;

public:

	void EnhancedMouse(const struct FInputActionValue& value);

	
};
