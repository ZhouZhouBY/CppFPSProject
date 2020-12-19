// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

float ASPlayerState::GetKillNum()
{
	return KillNum;
}

float ASPlayerState::GetBeKilledNum()
{
	return BeKilledNum;
}

void ASPlayerState::AddKillNum()
{
	++KillNum;
}

void ASPlayerState::AddBeKilledNum()
{
	++BeKilledNum;
}

void ASPlayerState::AddScore(float ScoreDelta)
{
	Score += ScoreDelta;
}

void ASPlayerState::SetName(FString NewName)
{
	name = NewName;
}

ASPlayerState::ASPlayerState()
{
	name = "默认玩家";
	KillNum = 0;
	BeKilledNum = 0;
}