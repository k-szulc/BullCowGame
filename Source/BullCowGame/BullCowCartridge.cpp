// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

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

    // HiddenWord = TEXT("abolishment");
    HiddenWord = TEXT("heat");
    PlayerLives = HiddenWord.Len();
    // PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); // debug line

    bGameOver = false;

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
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Hidden Word is %i chars long You idiot, try again !"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives left."), PlayerLives);
        return;
    }

    // check if isogram 
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("There must be no repeating letters, try again."));
        PrintLine(TEXT("You have %i lives left."), PlayerLives);
        return;
    }

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Bingo !"));
        EndGame();
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
    PrintLine(TEXT("Guess again, You have %i lives left."), PlayerLives);

}

bool UBullCowCartridge::IsIsogram(FString Guess)
{
    for (int32 i = 0 ; i < Guess.Len() ; i++)
    {
        for (int32 j = 0 ; j < Guess.Len() ; j++)
        {
            if (Guess[i] == Guess[j] && i != j)
            {
                return false;
            }
        }
    }
    return true;
}

FString UBullCowCartridge::CheckLetters(FString Guess)
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

