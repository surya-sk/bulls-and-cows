// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    WordToGuess = TEXT("action");
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Guess the 5 letter word.")); //hard-coded. Change later
    PrintLine(TEXT("Press ENTER to continue"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
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