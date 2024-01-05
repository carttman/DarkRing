// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EJAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) | GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) | GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) | GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) | GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class DARKRING_API UEJAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UEJAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeprops) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	//ATTRIBUTE_ACCESSORS(UEJAttributeSet, Health);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

};
