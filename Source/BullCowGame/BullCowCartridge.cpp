// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

// When the game starts
void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Guess the 5 letter word.")); //hard-coded. Change later
    PrintLine(TEXT("Press ENTER to continue"));
    GameInit();
}

// When the player hits enter
void UBullCowCartridge::OnInput(const FString& Input) 
{
    ClearScreen();
    if(Input == WordToGuess)
    {
        PrintLine(TEXT("You have guess it! Congratulations"));
        return;
    }
    else
    {
        PrintLine(TEXT("Wrong"));
    }
}

// Set guess word and print welcome message
void UBullCowCartridge::GameInit()
{
    WordToGuess = TEXT("action");
    Lives = 3;
}