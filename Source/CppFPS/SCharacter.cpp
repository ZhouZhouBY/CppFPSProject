// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 2.0;
	//创建弹簧臂
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	// 创建相机
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("weapon"));

	SpringArmComp->bUsePawnControlRotation = true;

	Score = 0;
	fireLoc = FVector(0);
	bulNum = 30;
	PlayerName = TEXT("Zhou");
	/*GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;*/
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	FVector CameraLoc = CameraComp->GetRelativeLocation();
	FRotator CameraRot = CameraComp->GetRelativeRotation();
	GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, "Camera" + CameraLoc.ToString());
}

void ASCharacter::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val * Speed);
}

void ASCharacter::MoveRight(float val)
{
	AddMovementInput(GetActorRightVector(), val * Speed);
}

void ASCharacter::NeedCrouch()
{
	Crouch(true);
}

void ASCharacter::NotNeedCrouch()
{
	UnCrouch(false);
}

void ASCharacter::Fire()
{
	FireServer();
}

void ASCharacter::DoFire()
{
	FTransform firingpoint = weapon->GetSocketTransform(TEXT("bullet"));
	FRotator ForwardVec;
	ForwardVec = CameraComp->GetComponentRotation();
	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();

	UWorld* const World = GetWorld(); // get a reference to the world  
	if (World)
	{
		// if world exists  
		GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, ForwardVec.ToString());
		ABullet* bul = World->SpawnActor<ABullet>(Bullet, firingpoint);
	}
	// GetWorld()->SpawnActor<ABullet>(Bullet, firingpoint, ForwardVec);
}


void ASCharacter::FireServer_Implementation()
{
	FireMulticast();
}

bool ASCharacter::FireServer_Validate()
{
	return true;
}

void ASCharacter::FireMulticast_Implementation()
{
	// if (!weaponCustom) return;

	FHitResult OutHit;
	FVector StarLoc, EndLoc;
	FVector ForwardVec;
	FCollisionQueryParams Param;

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		if (bulNum <= 0) {
			return;
		}
		--bulNum;
		GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, FString::SanitizeFloat(bulNum));
		StarLoc = CameraComp->GetComponentLocation();
		ForwardVec = CameraComp->GetForwardVector();
		EndLoc = StarLoc + ForwardVec * 3000;
		//MyOwner->GetActorEyesViewPoint(StarLoc, Rota);
		//EndLoc = StarLoc + Rota.Vector() * INT_MAX;
		Param.AddIgnoredActor(MyOwner);
		Param.AddIgnoredActor(this);
		Param.bTraceComplex = true;

		if (GetWorld()->LineTraceSingleByChannel(OutHit, StarLoc, EndLoc, ECollisionChannel::ECC_Visibility, Param))
		{
			//GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, OutHit.Location.ToString());
			/*UObject* act = OutHit.Actor->GetArchetype();
			GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, ToString));*/

			FName name = OutHit.Actor->GetFName();
			//GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, name.ToString());


			FVector hitLoc = OutHit.Location;
			FVector centerLoc = OutHit.Actor->GetActorLocation();
			float dis = (hitLoc - centerLoc).Size();
			if (name != "BP_Target_2")
			{
				fireLoc = FVector(0);
				Score += 0;
			}
			else
			{
				if (dis <= 20)
				{
					Score += 3;
				}
				else if (dis > 20 && dis <= 90) {
					Score += 2;
				}
				else if (dis > 90)
				{
					Score += 1;
				}
			}

			//DrawDebugBox(GetWorld(), OutHit.Location, FVector(10, 10, 10), FColor::Red, true, 1000.);


			//GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, FString::SanitizeFloat(Score));
			DrawDebugLine(GetWorld(), weapon->GetSocketLocation("Weapon"), OutHit.Location, FColor::Red, false, 0.1f, 0, 2);
			fireLoc = OutHit.Location;
			return;
		}
		else
		{
			DrawDebugLine(GetWorld(), weapon->GetSocketLocation("Weapon"), EndLoc, FColor::Red, false, 0.1f, 0, 2);
			fireLoc = FVector(0);
			return;
		}
		
	}
}

void ASCharacter::OnRep_Score()
{
	return;
}

void ASCharacter::Run()
{

}

void ASCharacter::UnRun()
{
	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* void ASCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASCharacter, Score);
} */

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//前后移动
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	//左右移动
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	//左右看
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	//上下看
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	//跳
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	//蹲
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::NeedCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::NotNeedCrouch);
	//射击
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASCharacter::Fire);
	//跑
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASCharacter::UnRun);
}

