// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

// When the game starts
void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();
    SetupGame();
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Guess the %d letter word."), WordToGuess.Len()); //hard-coded. Change later
    PrintLine(TEXT("Press ENTER to continue"));
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
        if(Input.Len() != WordToGuess.Len())
        {
            PrintLine(TEXT("The word is %d letters long. Try again"), WordToGuess.Len());
        }
        else
        {
            PrintLine(TEXT("Wrong word. Please try again"));
        }
    }
}

// Initalize variables 
void UBullCowCartridge::SetupGame()
{
    WordToGuess = TEXT("action");
    Lives = 3;
}