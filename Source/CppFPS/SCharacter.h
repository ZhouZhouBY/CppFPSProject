// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Weapon.h"
#include "SCharacter.generated.h"


UCLASS()
class CPPFPS_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//前后移动
	void MoveForward(float val);
	//左右移动
	void MoveRight(float val);
	//速度加成buff
	UPROPERTY(EditAnywhere, Category = "Buff")
	float Speed;
	//相机弹簧臂
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent* SpringArmComp;
	//相机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	FVector fireLoc;
	//武器

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	AWeapon* weaponCustom = nullptr;

	//蹲下
	void NeedCrouch();
	//起来
	void NotNeedCrouch();
	//射击
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void FireServer();

	UFUNCTION(NetMulticast, Reliable)
	void FireMulticast();

	//当前得分
	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Score")
	float Score;
	
	UFUNCTION()
	void OnRep_Score();

	/** 最大得分 */
	UPROPERTY(EditDefaultsOnly, Category = "Score")
	float MaxScore;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
