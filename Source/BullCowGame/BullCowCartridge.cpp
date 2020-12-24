#include "BullCowCartridge.h"
#include "WordList.h"

FPlayerScore PlayerScore;
// When the game starts
void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();

    ResetPlayerScore();

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
    Lives = WordToGuess.Len() * 2;
    bGameOver = false;
    // random places to show hints
    Rand1 = FMath::RandRange(0, WordToGuess.Len()-1);
    Rand2 = FMath::RandRange(0, WordToGuess.Len()-1);

    // print welcome messages
    PrintLine(TEXT("Welcome to Bulls and Cows!"));
    PrintLine(TEXT("Press Tab to enter/exit the terminal."));
    PrintLine(TEXT("Type help for more info and commands."));
    PrintLine(TEXT("Guess the %d letter isogram."), WordToGuess.Len());
    DisplayHints(WordToGuess);
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
    if(Guess == "exit")
    {
        FGenericPlatformMisc::RequestExit(false);
        return;
    }

    if(Guess == "help")
    {
        PrintLine(TEXT("An isogram is a word with no repeating \nletters."));
        PrintLine(TEXT("Bull: Right letter in right place."));
        PrintLine(TEXT("Cow: Right letter in wrong place."));
        PrintLine(TEXT("Type exit to quit the game."));
        PrintLine(TEXT("Type skip to skip current word."));
        PrintLine(TEXT("Type credits for credits."));
        return;
    }

    if(Guess == "credits")
    {
        PrintLine(TEXT("Game made by Surya Kashyap"));
        PrintLine(TEXT("Assets and starter content by GameDev.tv"));
        PrintLine(TEXT("Music: https://mixkit.co/free-stock-music/"));
        PrintLine(TEXT("This game is open-source."));
        PrintLine(TEXT("https://github.com/surya-sk/bull-cow-ue4"));
        PrintLine(TEXT("Contact: surya.sk05@outlook.com"));
        return;
    }

    if(Guess == "skip")
    {
        PrintLine(TEXT("The word was %s. Better luck next time."), *WordToGuess);
        PlayerScore.Skips++;
        UE_LOG(LogTemp, Warning, TEXT("Skips %d"), PlayerScore.Skips);
        EndGame();
        return;
    }

    if(Guess == "score")
    {
        PrintLine(TEXT("Correct: %d"), PlayerScore.Rights);
        PrintLine(TEXT("Skips: %d"), PlayerScore.Skips);
        PrintLine(TEXT("Wrong: %d"), PlayerScore.Wrongs);
        return;
    }

    if(Guess == WordToGuess)
    {
        PrintLine(TEXT("You have guessed it! Congratulations."));
        PlayerScore.Rights++;
        UE_LOG(LogTemp, Warning, TEXT("Rights %d"), PlayerScore.Rights);
        EndGame();
        return;
    }
    
    if(Guess.Len() != WordToGuess.Len())
    {
        PrintLine(TEXT("The word is %d letters long. Try again."), WordToGuess.Len());
        DisplayHints(WordToGuess);
        return;
    }

    // check if it is an isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The word does not have repeating letters."));
        DisplayHints(WordToGuess);
        return;
    }

    // decrease life when guess is wrong
    PrintLine(TEXT("You've lost a life."));
    DisplayHints(WordToGuess);
    --Lives;

    // show losing message when all lives are lost
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You've run out of lives. Game over."));
        PrintLine(TEXT("The word was %s. Better luck next time."), *WordToGuess);
        PlayerScore.Wrongs++;
        UE_LOG(LogTemp, Warning, TEXT("Wrongs %d"), PlayerScore.Wrongs);
        // end game after player runs out of lives
        EndGame();
        return;
    }

    // show bulls and cows
    FBullCowCount Score = GetBullsAndCows(Guess);
    PrintLine(TEXT("You have %d Bull(s) and %d Cow(s)."), Score.Bulls, Score.Cows);

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

// Displays hint for the word to guess
void UBullCowCartridge::DisplayHints(const FString& Word)
{
    FString Hint = FString::ChrN(Word.Len(), TEXT('-'));
    for (int32 i = 0; i < Word.Len(); i++)
    {
        if(i == Rand1 || i == Rand2)
        {
            Hint[i] = Word[i];
        }
    }
    
    PrintLine(TEXT("Hint: %s"), *Hint);
}

// Reset player score
void UBullCowCartridge::ResetPlayerScore()
{
    // reset player score
    PlayerScore.Rights = 0;
    PlayerScore.Skips = 0;
    PlayerScore.Wrongs = 0;
}