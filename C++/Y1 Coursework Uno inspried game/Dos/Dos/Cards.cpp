#include "Cards.h"

Card::Card(string v, string c)
// Constructor for card class
{
    value = v;
    colour = c;
}

string Card::GetValue()
// Returns the value of the given card
{
    return value;
}

string Card::GetColour()
// Returns the colour of the given card
{
    return colour;
}


string Card::show()
// Returns a string in the form "Card.colour Card.value"
{

    return colour + " " + value;
}

bool Card::Playable(string PrevVal, string PrevCol)
// Returns whether the card is playable based on the top pile of the discard pile
{
    if (colour == "Black")
    {
        return true;
    }
    else if (PrevCol == colour or PrevVal == value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool InValues(string item)
// Checks whether the item is in the values list
{
    for (string v : values)
    {
        if (item == v)
        {
            return true;
        }
    }
    return false;
}

bool InBlackValues(string item)
// Checks whether the item is in the blackvalues list
{
    for (string bv : blackvalues)
    {
        if (item == bv)
        {
            return true;
        }
    }
    return false;
}


bool InColours(string item)
// Checks whether the item is in the colour list
{
    for (string c : colours)
    {
        if (item == c)
        {
            return true;
        }
    }
    return false;
}

void SetToSentence(string& word)
// Sets an entered string to sentence case
{
    for (int i = 0; i < word.size(); i++)
    {
        word[i] = tolower(word[i]);
    }
    word[0] = toupper(word[0]);
}

void Card::Play(int& p, bool& reversed, string& pcolour, int& drawx)
// Add the special functionality of certain cards
{
    pcolour = colour; // Setting play colour
    cout << "Playing card " << show() << endl;
    bool valid = false;
    if (value == "Skip") // Increments/decrements the value for p depending on whether the order of play is reversed to ensure that the next player's turn is skipped
    {
        cout << "Skipping turn" << endl;
        if (!reversed)
        {
            p++;
        }
        else
        {
            p--;
        }
    }
    else if (value == "Reverse") // Reverses the order of play
    {
        cout << "Reversing order of play" << endl;
        reversed = not(reversed);
    }
    else if (value == "+2") // Causes the next player to have to draw 2 (more) cards
    {
        drawx += 2;
    }
    else if (colour == "Black")
    {
        if (value == "+4") // Causes the next player to have to draw 4 cards
        {
            drawx += 4;
        }
        while (!valid) // Loop for ensuring the player enters a valid colour of play
        {
            string ccolour; // Inputted colour for black cards
            cout << "Enter a new colour for play ";
            cin >> ccolour; 
            SetToSentence(ccolour);
            if (InColours(ccolour) and ccolour != "Black")
            {
                valid = true;
                pcolour = ccolour;
                cout << "New colour of play is " << ccolour;
            }
            else
            {
                cout << "Invalid colour, please enter Blue, Red, Green, Yellow" << endl;
            }
        }
    }
}

bool ValidCard(string v, string c)
// Checks whether a given card is valid
{
    if (InColours(c))
    {
        if (c == "Black")
        {
            if (InBlackValues(v))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (InValues(v))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
}

Card MakeCard(string v, string c)
// Creates a valid instance of a card using the valid card function
{
    if (ValidCard(v, c))
    {
        return Card(v, c);
    }
    else
    {
        throw(v + " " + c); // Throws an exception if the card which is created is invalid
    }
}

int FindEmptyPos(Card Deck[])
// Gives a new random empty position for the card object from make deck to be entered into
{
    int pos; 
    srand(time(0)); // Seeds the random number generator based on the current time, giving a unqiue deck each time
    while (true)
    { 
        pos = rand() % DECKSIZE; // Gives a random number in the range 0 <= pos < DECKSIZE
        if (Deck[pos].show() == "Black Null") // "Black Null" is the default value for a card so this checks whether another card has been placed in the space
        {
            return pos;
        }
    }
}

void MakeDeck(Card Deck[])
// AConstructs and returns a deck in a random order
{
    for (string c : colours)
    {
        if (c == "Black")
        {
            for (string bv : blackvalues) 
            {
                Deck[FindEmptyPos(Deck)] = MakeCard(bv, c); // Creates and adds all the black cards
            }
        }
        else
        {
            for (string v : values)
            {
                Deck[FindEmptyPos(Deck)] = MakeCard(v, c); // Creates and adds all the blue, red and yellow cards
            }
        }
    }
}


void Deal(stack<Card>& DrawDeck, Card Deck[], int PlayerNum, vector<vector<Card>>&PlayerHands)
// Fills in the player's hands and the draw deck
{
    vector<Card> PHand;
    int c = 0;
    for (int i = 0; i < PlayerNum; i++)
    {
        while (PHand.size() < HandSize) // Fills each player's hand
        {
            PHand.push_back(Deck[c]);
            c++;
        }
        PlayerHands.push_back(PHand); // Adds the filled hand to playerhands
        PHand.clear();
    }
    while (c < DECKSIZE) // Places the remaining cards in the deck into the draw pile
    {
        DrawDeck.push(Deck[c]);
        c++;
    }
}

void AddToTop(vector<Card>& V1, stack<Card>& V2, int pos)
// Adds the card in position pos of V1 to the top of v2
{
    if (pos == 12345)
    {
        pos = V1.size() - 1;
    }
    V2.push(V1[pos]);
    V1.erase(V1.begin() + pos);
}

void Draw(vector<Card>& ph, stack<Card>& dp)
// Adds the top card of the drawpile into the player's hand
{
    ph.push_back(dp.top());
    cout << "Drawing card : " << dp.top().show() << endl;
    dp.pop();
}
