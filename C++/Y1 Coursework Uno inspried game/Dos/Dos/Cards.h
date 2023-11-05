#include "Includes.h"
#include <ctime> // Allows the current time to be found by the program, used for seeding the random number generator used to create unique decks

const int DECKSIZE = 52;
const int HandSize = 7;
const string values[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "+2", "Reverse", "Skip" };
const string blackvalues[4] = { "+4", "+4", "ChangeColour", "ChangeColour"};
const string colours[5] = { "Black", "Blue", "Red", "Green", "Yellow" };

// Class for cards
class Card
{
private:
    string value;
    string colour;
public:
    // Constructor declaration
    Card(string v = "Null", string c = "Black");
    string GetValue();
    string GetColour();
    string show();
    bool Playable(string PrevVal, string PrevCol);
    void Play(int& p, bool& reverse, string& colour, int &drawx);
};
void SetToSentence(string& word);
bool InValues(string item);
bool InBlackValues(string item);
bool InColours(string item);
bool ValidCard(string v, string c);
Card MakeCard(string v, string c);
int FindEmptyPos(Card Deck[]);
void MakeDeck(Card Deck[]);
void Deal(stack<Card>& DrawDeck, Card Deck[],  int PlayerNum, vector<vector<Card>>&PlayerHands);
void AddToTop(vector<Card>& V1, stack<Card>& V2, int pos = 12345);
void Draw(vector<Card>& ph, stack<Card>& dp);
