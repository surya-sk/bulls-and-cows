#include "BullCowCartridge.h"
#include "WordList.h"

// When the game starts
void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();

    SetupGame();

    GetValidWords(Words);
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
    int32 RandomWordIndex = FMath::RandRange(0, GetValidWords(Words).Num()-1);
    WordToGuess = GetValidWords(Words)[RandomWordIndex];
    Lives = WordToGuess.Len();
    bGameOver = false;

    // print welcome messages
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Hidden word is %s"), *WordToGuess);
    PrintLine(TEXT("Guess the %d letter word."), WordToGuess.Len());
    PrintLine(TEXT("You have %d lives."), Lives);
}

// Restart the game after ending
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress ENTER to continue"));
}

// Validate guess and respond accordingly
void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if(Guess == WordToGuess)
    {
        PrintLine(TEXT("You have guessed it! Congratulations."));
        EndGame();
        return;
    }
    
    if(Guess.Len() != WordToGuess.Len())
    {
        PrintLine(TEXT("The word is %d letters long. Try again."), WordToGuess.Len());
        return;
    }

    // check if it is an isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The word does not have repeating letters."));
        return;
    }

    // decrease life when guess is wrong
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

    // show bulls and cows
    FBullCowCount Score = GetBullsAndCows(Guess);
    PrintLine(TEXT("You have %d Bulls and %d Cows."), Score.Bulls, Score.Cows);

    // show number of lives remaining
    PrintLine(TEXT("You have %d live(s) remaining."), Lives);
}

// Check if the input is an isogram
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    // check if there are repeating letters
    for(int32 i = 0; i < Word.Len(); i++)
    {
        for(int32 c = i + 1; c < Word.Len(); c++)
        {
            if(Word[i] == Word[c])
            {
                return false;
            }
        }
    }    
    return true;
}

// Return a list with isograms between 4 and 9 letters
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordsList) const
{
    TArray<FString> FilteredWordList;
    for(FString ThisWord : WordsList)
    {
        if(ThisWord.Len() >= 4 && ThisWord.Len() <= 8 && IsIsogram(ThisWord))
        {
            FilteredWordList.Emplace(ThisWord);
        }
    }
    return FilteredWordList;
}

// Gives the player bulls and cows via out paramters
FBullCowCount UBullCowCartridge::GetBullsAndCows(const FString& Guess) const
{
    FBullCowCount Count;
    for (int32 i = 0; i < Guess.Len(); i++)
    {
        if(Guess[i] == WordToGuess[i])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 j = 0; j < Guess.Len(); j++)
        {
            if(Guess[i] == WordToGuess[j])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}