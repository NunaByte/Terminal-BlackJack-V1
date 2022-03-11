#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "Utils.h"
#include "Utils2.h"
using namespace std;

const char * INPUT_ERROR_STRING = "Input error! Please try again.";

struct Card
{
    string cardFace;
    int value;
    bool isUsed;
};

struct Selection
{
    int row;
    int col;
};

enum PlayerGameState
{
    PGS_WIN = 0,
    PGS_LOSE,
    PGS_PUSH,
    PGS_NONE
};

struct Dealer
{
    char name;
    Card holding[17];
    int cardCount = 0;
    int cardValue = 0;
    PlayerGameState state;
    int balance;
};

struct Player
{
    char name;
    Card holding[3];
    int cardCount = 0;
    int cardValue = 0;
    PlayerGameState state;
    int balance;
};

void PlayGame(Player &player,Dealer &dealer,Card cards[4][13],bool &stillPlaying);
void SetCards(Card cards[4][13]);
void DealCards(Player &player, Dealer &dealer, Card cards[4][13], int count);
void DealCards(Player &player, Card cards[4][13], int count);
void DealCards(Dealer &dealer, Card cards[4][13], int count);
void calcTotal(Player &player, Dealer &dealer);
bool allCardsUsed(Card cards[4][13]);
void displayLogo();
void displayHand(Player &player);
void displayHand(Dealer &dealer);
void resetStats(Player &player, Dealer &dealer, Card cards[4][13]);

int main()
{
    srand(time(NULL));
    Dealer dealer;
    Player player;
    Card cards[4][13];
    int choice;
    bool stillPlaying = true;
    bool running = true;

    while(running)
    {
        ClearScreen();
        displayLogo();
        const int validInput[2] = {1,2};
        choice = GetInteger("Start Game(1)\nExit Game(2)\n\nEnter Selection: ",INPUT_ERROR_STRING,validInput,2);

        if(choice == 1)
        {
            stillPlaying = true;
            do
            {
            
            PlayGame(player, dealer, cards, stillPlaying);

            }while(stillPlaying);
        }
        else if(choice == 2)
        {
            break;
        }
    
    
    }

    return 0;
}



void PlayGame(Player &player,Dealer &dealer,Card cards[4][13], bool &stillPlaying)
{
    while(stillPlaying)
    {
        resetStats(player, dealer, cards);
        ClearScreen();
        displayLogo();
        SetCards(cards);
        DealCards(player, dealer, cards, 2);
        calcTotal(player, dealer);
        displayHand(player);
        displayHand(dealer);

        if((player.cardValue > dealer.cardValue) && (player.cardValue == 21))
        {
            cout << "Player has won with a BLACKJACK!";
            cout << endl;
            break;
        }
        else if((player.cardValue > dealer.cardValue) && (player.cardValue > 21))
        {
            cout << "Dealer has won, player has bust :(";
            cout << endl;
            break;
        }
        

        if((dealer.cardValue > player.cardValue) && (dealer.cardValue == 21))
        {
            cout << "Dealer has won with a BLACKJACK :(";
            cout << endl;
            break;
        }
        else if((dealer.cardValue > player.cardValue) && (dealer.cardValue > 21))
        {
            cout << "Player has won, dealer has bust";
            cout << endl;
            break;
        }
        else if(dealer.cardValue == player.cardValue)
        {
            cout << "There are no victors this round";
            cout << endl;
            break;
        }
    

        char validInput[2] = {'Y','N'};
        char playerChoice = GetCharacter("Player would you like to hit? (Y or N): ",INPUT_ERROR_STRING,validInput,2,CC_UPPER_CASE);
        if(playerChoice == 'Y')
        {
            DealCards(player, cards, 1);
            calcTotal(player, dealer);
            cout << "Player is dealt an extra card";
            ClearScreen();
            displayLogo();
            displayHand(player);
            displayHand(dealer);
            WaitForKeyPress();

            //Check for win after player hits
            if((player.cardValue > dealer.cardValue) && (player.cardValue == 21))
            {
                cout << "Player has won";
                cout << endl;
                break;
            }
            else if((player.cardValue > dealer.cardValue) && (player.cardValue > 21))
            {
                cout << "Dealer has won, player has bust :(";
                cout << endl;
                break;
            }
            
            if((dealer.cardValue > player.cardValue) && (dealer.cardValue == 21))
            {
                cout << "Dealer has won :(";
                cout << endl;
                break;
            }
            else if((dealer.cardValue > player.cardValue) && (dealer.cardValue > 21))
            {
                cout << "Player has won, dealer has bust";
                cout << endl;
                break;
            }
        }
        else if(playerChoice == 'N')
        {
            ClearScreen();
            displayLogo();
            displayHand(player);
            displayHand(dealer);
            cout << "Player decided to stay" << endl;
            WaitForKeyPress();
        }
        
        //Dealer hits till value is greater than 17
        while(dealer.cardValue < 17)
        {
            DealCards(dealer, cards, 1);
            calcTotal(player, dealer);
            ClearScreen();
            displayLogo();
            displayHand(player);
            cout << "Dealer draws another card" << endl;
            cout << "----------------------------------------";
            cout << endl;
            displayHand(dealer);
            WaitForKeyPress();
        }
        //Returns who has won or lost
        if((player.cardValue > dealer.cardValue) && (player.cardValue == 21))
        {
            cout << "Player has won";
            cout << endl;
            break;
        }
        else if((player.cardValue > dealer.cardValue) && (player.cardValue > 21))
        {
            cout << "Dealer has won, player has bust :(";
            cout << endl;
            break;
        }
        

        if((dealer.cardValue > player.cardValue) && (dealer.cardValue == 21))
        {
            cout << "Dealer has won :(";
            cout << endl;
            break;
        }
        else if((dealer.cardValue > player.cardValue) && (dealer.cardValue > 21))
        {
            cout << "Player has won, dealer has bust";
            cout << endl;
            break;
        }
        else if((dealer.cardValue > player.cardValue) && (dealer.cardValue < 21))
        {
            cout << "Dealer has won this round";
            cout << endl;
            break;
        }
        else if((dealer.cardValue < player.cardValue) && (dealer.cardValue < 21))
        {
            cout << "Player has won this round";
            cout << endl;
            break;
        }
        else if(dealer.cardValue == player.cardValue)
        {
            cout << "There is no victor this round";
            cout << endl;
        }
        
    }

    
        char playerRoundChoice;
        char validInput[2] = {'Y','N'};
        playerRoundChoice = GetCharacter("Would you like to play another round? (Y or N): ",INPUT_ERROR_STRING,validInput,2,CC_UPPER_CASE);

        if(playerRoundChoice == 'Y')
        {
            stillPlaying = true;
        }
        else if(playerRoundChoice == 'N')
        {
            stillPlaying = false;
            cout << "Thank you for playing Black Jack!";
        }
}


//Functions to deal cards to dealer or player
void DealCards(Player &player, Dealer &dealer, Card cards[4][13], int count)
{
    Selection deal;

    for(int i = 0; i < count; i++)
    {
        //Deal to player
        do
        {
            deal.row = rand() % 4;
            deal.col = rand() % 13;

            if(cards[deal.row][deal.col].isUsed != true)
            {
                if(player.cardCount > 1)
                {
                    player.holding[player.cardCount + i] = cards[deal.row][deal.col];
                }
                else
                {
                    player.holding[i] = cards[deal.row][deal.col];
                }
                cards[deal.row][deal.col].isUsed = true;
                player.cardCount++;
                break;
            }


        }while(cards[deal.row][deal.col].isUsed == false);

        //Deal to dealer
        do
        {
            deal.row = rand() % 4;
            deal.col = rand() % 13;

            if(cards[deal.row][deal.col].isUsed != true)
            {
               if(dealer.cardCount > 1)
                {
                    dealer.holding[player.cardCount + i] = cards[deal.row][deal.col];
                }
                else
                {
                    dealer.holding[i] = cards[deal.row][deal.col];
                }
                cards[deal.row][deal.col].isUsed = true;
                dealer.cardCount++;
                break;
            }

        }while(cards[deal.row][deal.col].isUsed == false);
     
    }
}

void DealCards(Player &player, Card cards[4][13], int count)
{
    Selection deal;

    for(int i = 0; i < count; i++)
    {
        do
        {
            deal.row = rand() % 4;
            deal.col = rand() % 13;

            if(cards[deal.row][deal.col].isUsed != true)
            {
                if(player.cardCount > 1)
                {
                    player.holding[player.cardCount + i] = cards[deal.row][deal.col];
                }
                else
                {
                    player.holding[i] = cards[deal.row][deal.col];
                }
                cards[deal.row][deal.col].isUsed = true;
                player.cardCount++;
                break;
            }

        }while(cards[deal.row][deal.col].isUsed == false);
     
    }

}

void DealCards(Dealer &dealer, Card cards[4][13], int count)
{
    Selection deal;

    for(int i = 0; i < count; i++)
    {
        do
        {
            deal.row = rand() % 4;
            deal.col = rand() % 13;

            if(cards[deal.row][deal.col].isUsed != true)
            {
                if(dealer.cardCount > 1)
                {
                    dealer.holding[dealer.cardCount + i] = cards[deal.row][deal.col];
                }
                else
                {
                    dealer.holding[i] = cards[deal.row][deal.col];
                }
                cards[deal.row][deal.col].isUsed = true;
                dealer.cardCount++;
            }

        }while(cards[deal.row][deal.col].isUsed == false);
    }
}

void calcTotal(Player &player, Dealer &dealer)
{
    int sum1{0};
    int sum2{0};

    for(int i = 0; i < player.cardCount; i++)
    {
        sum1 += player.holding[i].value;
    }
    player.cardValue = sum1;

    for(int i = 0; i < dealer.cardCount; i++)
    {
        sum2 += dealer.holding[i].value;
    }
    dealer.cardValue = sum2;
}

void displayHand(Player &player)
{
    cout << "PLAYER HAND" << endl;
    cout << "_____________" << endl;

    for(int i = 0; i < player.cardCount; i++)
    {
        cout << player.holding[i].cardFace << " " << player.holding[i].value;
        cout << endl;
    }

    cout << "HAND TOTAL: " << player.cardValue;
    cout << endl;
    cout << "----------------------------------------";
    cout << endl;
    
}

void displayHand(Dealer &dealer)
{
    cout << "DEALER HAND" << endl;
    cout << "_____________" << endl;

    for(int i = 0; i < dealer.cardCount; i++)
    {
        cout << dealer.holding[i].cardFace << " " << dealer.holding[i].value;
        cout << endl;
    }

    cout << "HAND TOTAL: " << dealer.cardValue;
    cout << endl;
    cout << "----------------------------------------";
    cout << endl;
}

void resetStats(Player &player, Dealer &dealer, Card cards[4][13])
{
    player.cardCount = 0;
    player.cardValue = 0;
    dealer.cardCount = 0;
    dealer.cardValue = 0;
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 13; c++)
        {
            cards[r][c].isUsed = false;
        }
    }
}



void displayLogo()
{
    cout << " _     _            _    _            _ " << endl;
    cout << "| |   | |          | |  (_)          | |" << endl;
    cout << "| |__ | | __ _  ___| | ___  __ _  ___| | __" << endl;
    cout << "| '_ \\| |/ _` |/ __| |/ / |/ _` |/ __| |/ /" << endl;
    cout << "| |_) | | (_| | (__|   <| | (_| | (__|   < " << endl;
    cout << "|_.__/|_|\\__,_|\\___|_|\\_\\ |\\__,_|\\___|_|\\_\\" << endl;
    cout << "                       _/ |                " << endl;
    cout << "                      |__/                " << endl;
}

void SetCards(Card cards[4][13])
{
    for(int r = 0; r < 4; r++)
    {
        for(int c = 0; c < 13; c++)
        {
            if(r == 0)
            {
                cards[r][c].cardFace = "Clover";
                if((c < 10) && (c != 0))
                {
                    cards[r][c].value = c+1;
                }
                else if(c == 0)
                {
                    cards[r][c].value = 11;
                }
                else
                {
                    cards[r][c].value = 10;
                }
                cards[r][c].isUsed = false;
            }
            else if(r == 1)
            {
                cards[r][c].cardFace = "Spade";
                if((c < 10) && (c != 0))
                {
                    cards[r][c].value = c+1;
                }
                else if(c == 0)
                {
                    cards[r][c].value = 11;
                }
                else
                {
                    cards[r][c].value = 10;
                }
                cards[r][c].isUsed = false;
            }
            else if(r == 2)
            {
                cards[r][c].cardFace = "Heart";
                if((c < 10) && (c != 0))
                {
                    cards[r][c].value = c+1;
                }
                else if(c == 0)
                {
                    cards[r][c].value = 11;
                }
                else
                {
                    cards[r][c].value = 10;
                }
                cards[r][c].isUsed = false;
            }
            else if(r == 3)
            {
                cards[r][c].cardFace = "Daimond";
                if((c < 10) && (c != 0))
                {
                    cards[r][c].value = c+1;
                }
                else if(c == 0)
                {
                    cards[r][c].value = 11;
                }
                else
                {
                    cards[r][c].value = 10;
                }
                cards[r][c].isUsed = false;
            }
        }
    }
}
