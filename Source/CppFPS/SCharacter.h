// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Weapon.h"
#include "Bullet.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sword")
	class UStaticMeshComponent* Sword;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sword")
	class UStaticMeshComponent* Rocket;

	// mesh
	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* MyMesh;

	//蹲下
	void NeedCrouch();
	//起来
	void NotNeedCrouch();
	//射击
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DoFire();

	UFUNCTION(Server, Reliable, WithValidation)
	void FireServer();

	UFUNCTION(NetMulticast, Reliable)
	void FireMulticast();

	// 拔枪
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void TakeOutWeapon();
	// 拔剑
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void TakeOutSword();
	

	// 放回武器
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ReturnWeapon();

	UFUNCTION()
	void OnRep_Score();

	/** 最大得分 */
	UPROPERTY(EditDefaultsOnly, Category = "Score")
	float MaxScore;

	UPROPERTY(BlueprintReadWrite, Category = "Init")
	bool CanAttack;
	UPROPERTY(BlueprintReadWrite, Category = "Init")
	bool IsSword;
	UPROPERTY(BlueprintReadWrite, Category = "Init")
	bool IsRocket;
	UPROPERTY(BlueprintReadWrite, Category = "Init")
	bool HasWeaponInHand;

	//物理子弹
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABullet> Bullet;

	/** 最大移动速度 */
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float MaxSpeed;

	//跑
	UFUNCTION(BlueprintCallable, Category = "Run")
	void Run();
	UFUNCTION(BlueprintCallable, Category = "Run")
	void UnRun();

	UPROPERTY(EditAnywhere)
	AActor* FireActor;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 子弹数
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Bullet")
	int bulNum;

	// 当前得分
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Score")
	float Score;

	// 角色名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FString PlayerName;
};
