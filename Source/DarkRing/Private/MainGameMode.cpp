// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "HealthBarWidget.h"


AMainGameMode::AMainGameMode()
{
	ConstructorHelpers::FClassFinder<UHealthBarWidget> tempHealthBarWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KEJ/DamageSystem/BP_HealthBarWidget.BP_HealthBarWidget_C'"));
	if (tempHealthBarWidget.Succeeded()) {
		healthBarWidget = tempHealthBarWidget.Class;
	}

}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	healthBarUI = CreateWidget<UHealthBarWidget>(GetWorld(), healthBarWidget);

	//healthBarUI->AddToPlayerScreen();
	//c++로 boss healthBar 만들려다 실패 여기있는 내용 전부 필요 없음

}