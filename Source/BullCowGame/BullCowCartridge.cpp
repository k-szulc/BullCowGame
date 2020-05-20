// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
#include <chrono>


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    auto start = std::chrono::high_resolution_clock::now();
    TArray<FString> ValidWords = GetValidWords(Words);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    PrintLine(TEXT("WordList count: %i"), ValidWords.Num());
    PrintLine(TEXT("HiddenWord is: %s"), *HiddenWord);
    PrintLine(TEXT("Duration %i"), duration.count());

    
    

}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{

    HiddenWord = TEXT("cake");
    PlayerLives = HiddenWord.Len();
    bGameOver = false;


    //auto start = std::chrono::high_resolution_clock::now();
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // DEBUG
    //PrintLine(TEXT("Duration %i"), duration.count());


    PrintLine(TEXT("Welcome into Bull and Cows game."));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), PlayerLives);
    PrintLine(TEXT("To start typing, please press TAB"));
    PrintLine(TEXT("Please input word and press ENTER"));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Please press ENTER to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{ 
    
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Bingo !"));
        EndGame();
        return;
    }

    if (!CheckWord(Guess))
    {
        return;
    }


    PrintLine(TEXT("Lost a life"));
    --PlayerLives;
    

    if (PlayerLives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You lost mate."));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        
        EndGame();
        return;
    }

    // show bull and cows
    PrintLine(CheckLetters(Guess));
    // Try again
    PrintLine(TEXT("\nGuess again, You have %i lives left."), PlayerLives);

}

bool UBullCowCartridge::CheckWord(const FString& Word) const
{
    if (Word.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Hidden Word is %i chars long, try again !"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives left."), PlayerLives);
        return false;
    }

    if(!IsIsogram(Word))
    {
        PrintLine(TEXT("There must be no repeating letters, try again."));
        PrintLine(TEXT("You have %i lives left."), PlayerLives);
        return false;
    }

    return true;
}


bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for(int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if(Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {   
                ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}


FString UBullCowCartridge::CheckLetters(const FString& Guess) const
{
    int32 BullLetter = 0;
    int32 CowLetter = 0;

    for (int32 i = 0; i < Guess.Len(); i++)
    {

        if (Guess[i] == HiddenWord[i])
        {
            ++BullLetter;
        }
        
        for (int32 j = 0 ; j < Guess.Len(); j++)
        {
            if(Guess[i] == HiddenWord[j])
            {
                ++CowLetter;
            }
        }

    }

    CowLetter -= BullLetter; // To exclude Bulls from Cows :D

    FString out = FString::Printf(TEXT("In Your attempt You had %i Bulls\nand %i Cows."), BullLetter, CowLetter);
    return out;
}

