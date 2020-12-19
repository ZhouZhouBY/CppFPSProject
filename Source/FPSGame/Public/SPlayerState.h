// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "PlayerState")
	float KillNum;

	UPROPERTY(BlueprintReadOnly, Category = "PlayerState")
	float BeKilledNum;

	UPROPERTY(BlueprintReadOnly, Category = "PlayerState")
	FString name;

public:

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	float GetKillNum();

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	float GetBeKilledNum();

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void AddKillNum();

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void AddBeKilledNum();

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void AddScore(float ScoreDelta);

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void SetName(FString NewName);

	ASPlayerState();
	
};
