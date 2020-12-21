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
        ProcessGuess(Input);
    }
}

// Setup the game up 
void UBullCowCartridge::SetupGame()
{
    // initalize variables
    WordToGuess = TEXT("action");
    Lives = WordToGuess.Len();
    bGameOver = false;

    // print welcome messages
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Guess the %d letter word."), WordToGuess.Len());
    PrintLine(TEXT("You have %d lives left."), Lives);
}

// Restart the game after ending
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress ENTER to continue"));
}

// Validate guess and respond accordingly
void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if(Guess == WordToGuess)
    {
        PrintLine(TEXT("You have guessed it! Congratulations."));
        EndGame();
        return;
    }

    // TODO: check if word is an isogram
    // if ()
    // {
    //     
    // }
    

    if(Guess.Len() != WordToGuess.Len())
    {
        PrintLine(TEXT("The word is %d letters long. Try again."), WordToGuess.Len());
        return;
    }

    //decrease life when guess is wrong
    PrintLine(TEXT("You've lost a life."));
    --Lives;

    // show losing message when all lives are lost
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You've run out of lives. Game over."));
        PrintLine(TEXT("The word was %s. Better luck next time."), *WordToGuess);
        // end game after player runs out of lives
        EndGame();
        return;
    }

    // show number of lives remaining
    PrintLine(TEXT("You have %d live(s) remaining."), Lives);
}