// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HAL/Platform.h"
#include "CppFPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CPPFPS_API ACppFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint32 point;
};
