// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class CPPFPS_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Target")
	class UStaticMeshComponent* target;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Center")
	class UStaticMeshComponent* center;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void search();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
