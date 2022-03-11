/*
    Step 1

    initDealer(dealer);
    initPlayer(player);
    bool stillPlaying = true;

    do
    {
        PlayGame()

    }while(stillPlaying);

    Play Game
    ---------------------------
    SetCards(); //Set the values and the faces of the cards in an array
    DealCards(player, dealer);
    calcTotal();
    checkHasWon(player, dealer);

    ask player if they want to hit //Take another card
    if(player wants to hit)
    {
        DealCards(player)
        checkHasWon(player, dealer);
    }

    while(player and dealer has not won)
    {
        DealCards(dealer)
        checkHasWon(player, dealer);
    }

    Ask player if they want to play another round
    if(yes)
    {
        stillPlaying = true;
    }
    else
    {
        stillPlaying = false;
    }

    Check Has Won
    -----------------------------
    setPlayerGameState(player,dealer);

    if(player has won and the dealer has not)
    {
        Congrats player has won the round!
    }
    else if(dealer has won and the player has not)
    {
        The dealer has won the round :(
    }
    else if(dealer has won and the player has won)
    {
        There are no victors this round
    }
    -----------------------------------------
*/