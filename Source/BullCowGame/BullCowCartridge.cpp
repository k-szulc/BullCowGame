// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
#include <chrono>


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{

    HiddenWord = TEXT("a");
    PlayerLives = HiddenWord.Len();
    bGameOver = false;

    // DEBUG
    PrintLine(TEXT("WordList %i"), Words.Num());
    int32 counter = 0;
    TArray<FString> HiddenWords = {};

    auto start = std::chrono::high_resolution_clock::now();

    for (FString i : Words)
    {
        if (IsIsogram(i))
        {   
            if(i.Len() >= 4 && i.Len() <= 8)
            {
                ++counter;
            }
            
        }
    }
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // DEBUG
    PrintLine(TEXT("Duration %i"), duration.count());


    // DEBUG
    PrintLine(TEXT("Isograms %i"), counter);

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

void UBullCowCartridge::ProcessGuess(FString Guess)
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
    PrintLine(CheckLetters(Guess,HiddenWord));
    // Try again
    PrintLine(TEXT("\nGuess again, You have %i lives left."), PlayerLives);

}

bool UBullCowCartridge::CheckWord(FString Word) const
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

// bool UBullCowCartridge::IsIsogram(FString Word) const
// {
//     for (int32 i = 0 ; i <= Word.Len() - 1 ; i++)
//     {
//             if (Word[i] == Word[i + 1])
//             {
//                 return false;
//             }
//     }
//     return true;
// }

bool UBullCowCartridge::IsIsogram(FString Word) const
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


FString UBullCowCartridge::CheckLetters(FString Guess, FString Word) const
{
    int32 BullLetter = 0;
    int32 CowLetter = 0;

    for (int32 i = 0; i < Guess.Len(); i++)
    {

        if (Guess[i] == Word[i])
        {
            ++BullLetter;
        }
        
        for (int32 j = 0 ; j < Guess.Len(); j++)
        {
            if(Guess[i] == Word[j])
            {
                ++CowLetter;
            }
        }

    }

    CowLetter -= BullLetter; // To exclude Bulls from Cows :D

    FString out = FString::Printf(TEXT("In Your attempt You had %i Bulls\nand %i Cows."), BullLetter, CowLetter);
    return out;
}

