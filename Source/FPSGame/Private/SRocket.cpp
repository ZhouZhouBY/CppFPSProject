// Fill out your copyright notice in the Description page of Project Settings.


#include "SRocket.h"
#include "Kismet/GameplayStatics.h"

void ASRocket::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner && RocketBullet) {
		FVector EyeLocation;
		FRotator EyeRotation;
		FVector StartLocation;
		FVector ForwardVec;
		FVector EndLocation;

		StartLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
		ForwardVec = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
		EndLocation = StartLocation + ForwardVec * 10000;

		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);
		// Particle "Target" Parameter
		FVector TraceEndPoint = EndLocation;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		FRotator MuzzleRotation = MeshComp->GetSocketRotation(MuzzleSocketName);
		FActorSpawnParameters SpawnParas;
		SpawnParas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(RocketBullet, MuzzleLocation, MuzzleRotation, SpawnParas);

		if (FireSound) {
			UGameplayStatics::PlaySound2D(this, RocketFireSound);
		}
	}
}