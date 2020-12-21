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
    else  // keep playing the game
    {
        if(Input == WordToGuess)
        {
            PrintLine(TEXT("You have guessed it! Congratulations"));
            EndGame();
        }
        else
        {
            //decrease life when guess is wrong
            --Lives;
            if(Lives > 0)
            {
                if(Input.Len() != WordToGuess.Len())
                {
                    PrintLine(TEXT("The word is %d letters long. You've lost"), WordToGuess.Len());
                }
                PrintLine(TEXT("You've lost a life. %d remaining."), Lives);
            }
            else
            {
                //End game after player runs out of lives
                PrintLine(TEXT("You've run out of lives. Game over."));
                EndGame();
            }
            
            
        }
    }
}

// Setup the game up 
void UBullCowCartridge::SetupGame()
{
    // Initalize variables
    WordToGuess = TEXT("action");
    Lives = WordToGuess.Len();
    bGameOver = false;

    // Print welcome messages
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Guess the %d letter word."), WordToGuess.Len());
    PrintLine(TEXT("You have %d lives left."), Lives);
    PrintLine(TEXT("Press ENTER to continue"));
}

// Restart the game after ending
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
}