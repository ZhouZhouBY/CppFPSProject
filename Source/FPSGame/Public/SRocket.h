// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SRocket.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API ASRocket : public ASWeapon
{
	GENERATED_BODY()

protected:
	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = "RocketBullet")
	TSubclassOf<AActor> RocketBullet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class USoundBase* RocketFireSound;
	
};
