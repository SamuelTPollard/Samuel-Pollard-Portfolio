#include "Testing.h"

int CChoice; // Stores the card which the player chose to play
int drawx = 0; // Stores the number of cards the player need to draw, used for +2/ +4 cards as well as drawing a card when they do not have a card to player
int p = 0; // Stores the index of the current player's hand 
int PlayerNum; // The number of players of the game, entered by the user
bool CanPlay; // Detects whether the player has a playable card 
bool GameWon = false; // Used to create the main game loop, set to true when a player runs out of cards
bool hasp2; // Detects whether the player has a +2 card to allow them to stack it on a previously played +2 card
bool newgame = false; // Whether or not a new game is needs to be created
bool Reversed = false; // When false, the players play in a normal order, when true the players play in a reverse order
bool valid = false; // Used to create loops for inputs to ensure a valid value is inputted
char choice; // Used to store the choice of 'y' or 'n' when the player is given a yes or no choice
string PlayColour = " "; // Stores the current colour of play
stack<Card>DiscardPile; // Stores the cards in the discard pile
stack<Card>DrawPile; // Stores the cards in the draw pile
vector<vector<Card>>PlayerHands; // Stores each player's hand of cards

int ResetConsole(int pnum = 0, bool mesg = false, bool doscheck = false)
{
    // Function with three different versions based on the value of entered bools
    if (mesg) // Console pause and reset with message
    {
        cout << '\n' << "Press any key to end turn " << "..." << endl;
        _getch(); // Pauses play until a character is entered
        system("CLS");  // Clears text in console
        cout << '\n' << "Press any key to start and show cards of player " << pnum << "..." << endl;
        _getch();
    }
    else if (doscheck) // Fake console pause for when the player only has two cards left
    {
        char l; // Stores each letter the player enters when they only have two cards left to check if they type 'dos'
        cout << '\n' << "Press any key to end turn" << "..." << endl;
        l = _getch();
        if (tolower(l) == 'd')
        {
            l = _getch();
            if (tolower(l) == 'o')
            {
                l = _getch();
                if (tolower(l) == 's')
                {
                    cout << "You said 'DOS', you don't have to draw any cards" << endl;
                    return 0;
                }
            }
        }
        cout << "You failed to say 'DOS', drawing 2 cards" << endl;
        Draw(PlayerHands[p], DrawPile);
        Draw(PlayerHands[p], DrawPile);
        return 0;
    }
    system("CLS");
    return 0;
}

void setp()
// Used to move between player's turns
{
    if (!Reversed) // Normal turn order
    {
        p++;
        if (p >= PlayerNum) // Resets turns back to player 1 when the p becomes out of the playerhands range, taking into account skip cards which will cause it to be 2 higher than it's normal maximum value
        {
            p = p - PlayerNum;
        }
    }
    else // Reversed turn order
    {
        p--;
        if (p <= -1)
        {
            p = p + PlayerNum;
        }
    }
}

int main()
{
    while (!valid)
    {
        // Main menu screen for tuturial and main game
        string option; //Stores the player's choice in the main menu screen
        cout << "Welcome to DOS" << endl;
        cout << "Type \'PLAY\' to continue to game or \'HELP\' to learn how to play: ";
        cin >> option;
        SetToSentence(option); // Sets input to sentence case
        cout << endl;
        if (option == "Play")
        {
            valid = true;
        }
        else if (option == "Help")
        {
            // Dos tutorial text
            cout << "DOS is an Uno inspired card game." << endl <<
                "The goal of the game is to be first player to run out of cards." << endl <<
                "A card of the same value or colour as the previously played card." << endl << 
                "Between player's turns the screen is cleared and the next player's hand is not shown until any key is pressed." << endl << 
                "In order to choose a card to play, enter the number shown before the card." << endl << 
                "When playing a card results in the player only having two cards left, the player must type \"DOS\" or they will have to draw two cards." << endl;
        }
        else if(option == "Test")
        {
            bool sucess = RunTests();
            if (sucess)
            {
                cout << "Testing sucessful" << endl;
            }
            else
            {
                cout << "Testing unsucessful" << endl;
            }
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }
    cout << "Checking for game save..." << endl;
    valid = false;
    if (CheckForFile())
    {
        while (!valid)
        {
            // Loop to ensure a valid choice for loading a file is made
            cout << "File found, would you like to load it (y/n)?";
            choice = _getch();
            if (choice == 'y')
            {
                bool error = false;
                try
                {
                    ReadFromFile(PlayerNum, p, PlayerHands, DiscardPile, DrawPile, PlayColour, drawx, Reversed);
                }
                catch (string mesg) // Detects when an invalid card is found
                {
                    // Resets any values which were set to their original values when an error is detected in the file
                    error = true;
                    ClearFile();
                    p = 0;
                    Reversed = false;
                    drawx = 0;
                    PlayerHands.clear();
                    DrawPile.empty();
                    DiscardPile.empty();
                    newgame = true;
                    PlayerNum = NAN;
                    error = true;
                    valid = true;
                    cout << endl << mesg << endl;
                }
                if (!error)
                {
                    valid = true;
                }
            }
            else if (choice == 'n')
            {
                cout << endl << "Starting new game" << endl;
                ClearFile();
                valid = true;
                newgame = true;
            }
            else
            {
                cout << endl << "Invalid choice" << endl;
            }
        }
    }
    else
    {
        cout << "No game file found, starting new game..." << endl;
        newgame = true;
    }
    if (newgame)
    {
        valid = false;
        Card Deck[DECKSIZE];
        MakeDeck(Deck);
        while (!valid)
        {
            // Loop to ensure a valid number of players for the game is chosen
            cout << "Enter a number of players between 2 and 4: ";
            PlayerNum = _getch() - '0'; // Adjusts the value from unicode char to be equivilant to if an int was entered
            cout << char(PlayerNum + '0') << endl;
            if (PlayerNum >= 2 and PlayerNum <= 4)
            {
                valid = true;
            }
            else
            {
                cout << endl << "Invalid player number" << endl;
            }
        }
        Deal(DrawPile, Deck, PlayerNum, PlayerHands);
        valid = false;
        ResetConsole();
        while (!valid)
        {
            // Ensures the top of the discard pile is not a black card
            DiscardPile.push(DrawPile.top());
            DrawPile.pop();
            if (DiscardPile.top().GetColour() != "Black")
            {
                valid = true;
            }
        }
        valid = false;
        PlayColour = DiscardPile.top().GetColour();
    }
    while (!GameWon) // Main game loop
    {
        CanPlay = false; // Sets each of the bools set based on the player's hand to their default values
        hasp2 = false;
        valid = false;
        ResetConsole(p+1, true); // Allows the player to end their turn by pressing any key, not showing the next players hand until another key is pressed
        cout << "Top of discard pile is " << DiscardPile.top().show() << endl;
        cout << "Current valid colour is " << PlayColour << endl;
        cout << "Player " << p + 1 << " cards :" << endl;
        // Prints the player's cards 
        int pc = 1; // Used to show the number corresponding to each card in the player's hand
        for (Card c : PlayerHands[p])
        {
            cout << pc << ": " << c.show() << endl;
            if (drawx == 0) // Used to ensure that the player can only play if they have no cards to draw caused by a +4 or +2 being played by the previous player
            {
                if (c.Playable(DiscardPile.top().GetValue(), PlayColour))
                    // Checks whether the player has any cards which are playable in the current situation
                {
                    CanPlay = true;
                }
            }
            // Stops the player from playing when a +4 card has been played
            else if (DiscardPile.top().GetValue() == "+4")
            {
                CanPlay = false;
            }
            else
            {
                // Checks whether the player can stack a +2 card on a previously played +2 card to cause the next player to have to draw 4 cards
                if (c.GetValue() == "+2")
                {
                    hasp2 = true;
                    CanPlay = true;
                }
            }
            pc++;
        }
        if (!CanPlay)
        {
            if (drawx == 0)
            {
                cout << "No valid cards to play " << endl;
                drawx++;
            }
            else
            {
                cout << "No cards to counter pick-up cards" << endl;
            }
            while (drawx != 0)
                // Drawing cards loop
            {
                Draw(PlayerHands[p], DrawPile);
                drawx--;
                // Adds the discard pile to the draw pile when the draw pile becomes empty.
                if (DrawPile.size() == 0)
                {
                    Card TempTop; // Values used to ensure that the last played card is still the same even when the discard pile is flipped and used as the draw pile
                    TempTop = DiscardPile.top(); 
                    DiscardPile.pop();
                    cout << "Discard pile empty, adding discard pile to draw pile" << endl;
                    while (DiscardPile.size() != 0)
                    {
                        DrawPile.push(DiscardPile.top());
                        DiscardPile.pop();
                    }
                    DiscardPile.push(TempTop);
                }
            }
        }
        else // The player is able to play a card
        {
            if (!hasp2)
            {
                // Normal card playing loop
                while (!valid)
                {
                    // Validation for input for which card the player wants to play
                    cout << "Please choose a playable card number...";
                    cin >> CChoice;
                    CChoice--;
                    if (CChoice >= 0 and CChoice <= PlayerHands[p].size() - 1)
                    {
                        if (PlayerHands[p][CChoice].Playable(DiscardPile.top().GetValue(), PlayColour))
                        {
                            valid = true;
                        }
                        else
                        {
                            cout << "This card is not playable" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid card number" << endl;
                        // Clears and ignores the input if an incorrect data type was entered
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                }
            }
            else
            {
                // Allows a player to play a +2 card over a previously played +2 card in order to cause the next player to have to draw 4 cards
                while (!valid)
                {
                    cout << "Please choose a +2 card number...";
                    cin >> CChoice;
                    CChoice--;
                    if (PlayerHands[p][CChoice].GetValue() == "+2")
                    {
                        valid = true;
                    }
                    else
                    {
                        cout << "This card is not a +2 card" << endl;
                    }
                }
            }
            AddToTop(PlayerHands[p], DiscardPile, CChoice); // Moves the played card from the player's hand to the top of the discard pile
            valid = false;
            if (PlayerHands[p].size() == 2) // Triggers the 'Dos' input prompt if the player has only 2 cards left after playing a card
            {
                ResetConsole(p, false, true);
            }
            else if (PlayerHands[p].size() == 0) // Detects whether a player has ran out cards
            {
                cout << "Player " << p + 1 << " wins" << endl;
                GameWon = true;
            }
            else
            {
                hasp2 = false;
            }
            DiscardPile.top().Play(p, Reversed, PlayColour, drawx); // Triggers the special avability of a card if it has one and sets the new play colour
        }
        setp();
        WriteToFile(PlayerNum, p, PlayerHands, DiscardPile, DrawPile, PlayColour, drawx, Reversed); // Writes the current state of the game to a file
    }
    ClearFile();
    valid = false;
    // Creates the loop to check whether the player wants to play again
    while (!valid)
    {
        cout << "Would you like to play again? (y/n) " << endl;
        choice = _getch();
        if (tolower(choice) == 'y') // Resets the game back to its original state
        {
            p = 0;
            drawx = 0;
            Reversed = false;
            GameWon = false;
            ClearFile();
            PlayerHands.clear();
            DrawPile.empty();
            DiscardPile.empty();
            main();
        }
        else if (tolower(choice) == 'n')
        {
            valid = true;
        }
        else
        {
            cout << "Invalid input, please enter \'y\' or \'n\'" << endl;
        }
    }
    return 0;
}