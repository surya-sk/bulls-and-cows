#include "BullCowCartridge.h"

// When the game starts
void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();
    SetupGame();
}

// When the player hits enter
void UBullCowCartridge::OnInput(const FString& Input) 
{
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        if(Input == WordToGuess)
        {
            PrintLine(TEXT("You have guessed it! Congratulations"));
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
}

// Initalize variables 
void UBullCowCartridge::SetupGame()
{
    WordToGuess = TEXT("action");
    Lives = 3;
    bGameOver = false;

    //Print welcome messages
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Guess the %d letter word."), WordToGuess.Len());
    PrintLine(TEXT("Press ENTER to continue"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    SetupGame();
}