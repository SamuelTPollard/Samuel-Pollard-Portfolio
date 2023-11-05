#include "Files.h"

bool CheckForFile()
// Checks whether there is already a save file
{
	ifstream CardFile;
	string Text;
	CardFile.open("Game.txt");
	getline(CardFile, Text);
	if (Text == "")
	{
		return false;
	}
	else
	{
		return true;
	}
	CardFile.close();
}

void GetValueColour(string c, string& value, string& colour)
// Seperates a string in the form value,string
{
	bool vcswitch = false; // Used to load the value, value from the first string and the colour value from the second string
	// String seperation code adapted from java2blog: https://java2blog.com/split-string-space-cpp/
	string vc;
	stringstream s(c);
	while (getline(s, vc, ','))
	{
		if (!vcswitch)
		{
			value = vc;
			vcswitch = true;
		}
		else
		{
			colour = vc;
			vcswitch = false;
		}
	}
}

void SeperateByComma(vector<Card>& temphand, string c) 
// Builds a card and adds it to temphand from a string in the form value,string
{
	string value;
	string colour;
	GetValueColour(c, value, colour);
	try
	{
		temphand.push_back(MakeCard(value, colour));
	}
	catch (string CardName) // Detects if an error is thrown from an invalid card, if there is the file is erased
	{
		throw("Invalid Card, " + CardName + " erasing file...");
	}
}

void SeperateByComma(stack<Card>& tempdeck, string c) 
// Builds a card and adds it to tempdeck from a string in the form value,string
{
	string value;
	string colour;
	GetValueColour(c, value, colour);
	try
	{
		tempdeck.push(MakeCard(value, colour));
	}
	catch (string CardName) // Detects if an error is thrown from an invalid card, if there is the file is erased
	{
		throw("Invalid Card, " + CardName + " erasing file...");
	}
}

void ReadFromFile(int& PlayerNum, int& p, vector<vector<Card>>& PlayerHands, stack<Card>& DiscardPile, stack<Card>& DrawPile, string& PlayColour, int& drawx, bool& Reversed)
// Reads from a text file and sets the values of each hand, the draw and discard piles, and key variables 
{
	ifstream CardFile;
	string FileText;
	CardFile.open("Game.txt");
	int lineno = 1;
	while (getline(CardFile, FileText))
	{
		stringstream ssin(FileText);
		string c;
		vector<Card> temphand;
		switch (lineno)
		{
		case 1: // Loading player number
			PlayerNum = int(FileText[0]) - '0'; // Converting from unicode value to numerical value
			if (PlayerNum > 4 or PlayerNum <= 0)
			{
				throw("Player number invalid, erasing file");
			}
			break;
		case 2: // Loading current player
			p = int(FileText[0]) - '0';  
			if (p > PlayerNum - 1 or p < 0)
			{
				throw("Turn number invalid, erasing file");
			}
			break;
		case 3: // Loads player 1's cards
			while (getline(ssin, c, ' ')) 
			{
				SeperateByComma(temphand, c); 
			}
			PlayerHands.push_back(temphand); 
			temphand.clear();
			break;
		case 4: // Loads player 2's cards
			while (getline(ssin, c, ' ')) 
			{
				SeperateByComma(temphand, c);
			}
			PlayerHands.push_back(temphand); 
			temphand.clear();
			break;
		case 5: // Loads player 3's cards if there are three more more players
			if (PlayerNum >= 3)
			{
				while (getline(ssin, c, ' ')) 
				{
					SeperateByComma(temphand, c); 
				}
				PlayerHands.push_back(temphand); 
				temphand.clear();
			}
			break;
		case 6: // Loads player 4's cards if there are 4 players
			if (PlayerNum == 4)
			{
				while (getline(ssin, c, ' ')) 
				{
					SeperateByComma(temphand, c);
				}
				PlayerHands.push_back(temphand); 
				temphand.clear();
				break;
			}
			break;
		case 7: // Loads the discard pile
			while (getline(ssin, c, ' '))
			{
				SeperateByComma(DiscardPile, c); 
			}
			break;
		case 8: // Loads the draw pile
			while (getline(ssin, c, ' '))
			{
				SeperateByComma(DrawPile, c); 
			}
			break;
		case 9: // Loads the play colour
			PlayColour = FileText; 
			if (!colours->find(PlayColour) or PlayColour == "Black")
			{
				throw("Invalid play colour, clearing file");
			}
			break;
		case 10: // Loads drawx value
			if (size(FileText) == 1)
			{
				drawx = int(FileText[0]) - '0'; // 1 digit drawx value
			}
			else
			{
				drawx = (int(FileText[0]) - '0') + (int(FileText[1]) - '0'); // two digit drawx value
			}
			break;
		case 11: // Loads reversed value
			Reversed = int(FileText[0]);
			break;
		};
		lineno++;
	}
	CardFile.close();
}

void WriteToFile(int PlayerNum, int p, vector<vector<Card>>PlayerHands, stack<Card> DiscardPile, stack<Card> DrawPile, string PlayColour, int drawx, bool Reversed)
// Writes each player hands, the draw and discard pile, and the key variables to a text file
{
	ofstream CardFile("Game.txt");
	string reversetext; // Used to allow the discard and draw pile to be written in reverse, ensuring they are read in the correct order
	CardFile << PlayerNum << endl; // Writes the player number
	CardFile << p << endl; // Writes the current player's turn
	for (vector<Card> h  : PlayerHands) // Writes each player's hand with each card being in the for value,colour
	{
		for (Card c : h)
		{
			CardFile << c.GetValue() + "," + c.GetColour() + " ";
		}
		CardFile << endl;
	}
	for (int i = PlayerNum; i < 4; i++) // Creates blank lines where the 3rd and 4th player's hands would be if they are not needed due to the number of player. This ensure that each value is always read from the same line regardless of player number
	{
		CardFile << endl;
	}
	while (DiscardPile.size() != 0) // Writes the discard pile to the file
	{
		Card c = DiscardPile.top();
		reversetext.insert(0, c.GetValue() + "," + c.GetColour() + " "); // Pushes the text to the front of the string rather than onto the end to ensure it is read in the correct order
		DiscardPile.pop();
	}
	CardFile << reversetext;
	reversetext = "";
	CardFile << endl;
	while (DrawPile.size() != 0) // Writes the draw pile to the file
	{
		Card c = DrawPile.top();
		reversetext.insert(0, c.GetValue() + "," + c.GetColour() + " ");
		DrawPile.pop();
	}
	CardFile << reversetext;
	reversetext = "";
	CardFile << endl;
	CardFile << PlayColour << endl; // Writes the current colour of play to the file
	CardFile << drawx << endl; // Writes the current number of cards the next player needs to draw
	CardFile << Reversed; // Writes reversed value to file
	CardFile.close();
}

void ClearFile()
// Clears the game save file
{
	ofstream CardFile("Game.txt");
	CardFile << "";
	CardFile.close();
}