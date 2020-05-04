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
    HiddenWord = TEXT("cake");
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
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Bingo !"));
        EndGame();
        return;
    }

    // // check if isogram
    // if(!IsIsogram)
    // {
    //     PrintLine(TEXT("There are no repeating letters, try again."));
    // }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Hidden Word is %i chars long You idiot, try again !"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives left."), PlayerLives);
        return;
    }

    PrintLine(TEXT("Lost a life"));
    --PlayerLives;
    

    if (PlayerLives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You fuckin lost mate."));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        
        EndGame();
        return;
    }

    // show bull and cows
    PrintLine(TEXT("Guess again, You have %i lives left."), PlayerLives);
    

    


 /*    else
    {
        PrintLine(TEXT("Nope."));

        if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("Hidden Word is %i chars long You idiot, try again !"), HiddenWord.Len());
        }
        else
        {
            // check if isogram
            int64 CorrectLetters = 0;

            for (int a = 0; a < HiddenWord.Len(); a++)
            {

                if (Guess[a] == HiddenWord[a])
                {
                    ++CorrectLetters;
                }
            }

            PrintLine(TEXT("In Your stupid attempt You had %i correct letters, and %i wrong. Get better kid! "), CorrectLetters, HiddenWord.Len() - CorrectLetters);
        }

        PrintLine(TEXT("You have %i lives left."), PlayerLives);

        if (PlayerLives == 0)
        {
            PrintLine(TEXT("You fuckin lost mate."));
            EndGame();
        }
    }
     */
}
