// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
#include "SHealthComponent.h"
#include "SPlayerState.h"

ASGameMode::ASGameMode()
{
	// Time = 100.0f;

	// GameStateClass = ASGameState::StaticClass();
	PlayerStateClass = ASPlayerState::StaticClass();
}

APlayerController* ASGameMode::CheckAnyDied()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn()) {
			APawn* MyPawn = PC->GetPawn();
		USHealthComponent* HealthComp = Cast<USHealthComponent>(MyPawn->GetComponentByClass(USHealthComponent::StaticClass()));
			if (ensure(HealthComp) && HealthComp->GetHealth() <= 0.0f) {
				return PC;
			}
		}
	}
	return nullptr;
}