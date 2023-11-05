#include "Cards.h"
#include <fstream>
#include <sstream>

bool CheckForFile();
void GetValueColour(string c, string& value, string& colour);
void SeperateByComma(vector<Card>& temphand, string c);
void SeperateByComma(stack<Card>& temphand, string c);
void ReadFromFile(int& PlayerNum, int& p, vector<vector<Card>>& PlayerHands, stack<Card>& DiscardPile, stack<Card>& DrawPile, string &PlayColour, int &drawx, bool& Reversed);
void WriteToFile(int PlayerNum, int p, vector<vector<Card>>PlayerHands, stack<Card> DiscardPile, stack<Card> DrawPile, string PlayColour, int drawx, bool Reversed);
void ClearFile();
