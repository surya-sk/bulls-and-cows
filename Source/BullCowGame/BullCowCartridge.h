// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

struct FPlayerScore
{
	int32 Rights = 0;
	int32 Wrongs = 0;
	int32 Skips = 0;	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordsList) const;
	FBullCowCount GetBullsAndCows(const FString& Guess) const;
	void DisplayHints(const FString& Word);
	void ResetPlayerScore();

	// Your declarations go below!
	private:
	FString WordToGuess;
	int32 Lives;
	bool bGameOver;
	int32 Rand1, Rand2;

};
