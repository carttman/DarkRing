// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InvenComponent.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ITEM_SPHERE,
	ITEM_CUBE,
	ITEM_CAPSULE,

	ITEM_MAX
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	EItemType type;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* Thumbnail;

	UPROPERTY(VisibleAnywhere)
	FString name;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKRING_API UInvenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInvenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	TArray<FItemData> myItems;
};
