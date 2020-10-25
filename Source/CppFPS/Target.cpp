// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	center = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Center"));
	
	target = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target"));
	RootComponent = center;
	target->SetupAttachment(center);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	/*FVector loc = GetActorLocation();
	GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, "loc" + loc.ToString());
	FVector loc1 = this->center->GetRelativeLocation();
	GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, "loc1" + loc1.ToString());*/
}

void ATarget::search()
{

}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	search();
}

