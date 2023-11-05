#include "Testing.h"

const string InvalidColours[4] = { " ", "Pink", "1234", "Dog" }; // Array containing invalid strings for card colour
const string InvalidValues[5] = { "-1", "+3", "Blue", "Black", "10" }; // Array containing invalid strings for card value

bool TestValidCard()
// Tests the valid card function works for all possible cards as well as checking it can correctly identify invalid cards
{
    for (string c : colours)
    {
        if (c == "Black")
        {
            for (string bv : blackvalues) 
            {
                if (!ValidCard(bv, c)) // Tests valid black cards
                {
                    throw("Valid Card test failed" + bv + " " + c + " falsely labelled as invalid");
                }
            }
            for (string v : values)
            {
                if (ValidCard(v, c)) // Tests invalid black cards
                {
                    throw("Valid Card test failed" + v + " " + c + " falsely labelled as invalid");
                }
            }
            for (string iv : InvalidValues)
            {
                if (ValidCard(iv, c)) // Tests invalid black cards
                {
                    throw("Valid Card test failed" + iv + " " + c + " falsely labelled as invalid");
                }
            }
        }
        else
        {
            for (string v : values)
            {
                if (!ValidCard(v, c)) // Tests valid Blue, Red, and Yellow cards
                {
                    throw("Valid Card test failed" + v + " " + c + " falsely labelled as invalid");
                }
            }
            for (string bv : blackvalues)
            {
                if (ValidCard(bv, c)) // Tests invalid Blue, Red, and Yellow cards
                {
                    throw("Valid Card test failed" + bv + " " + c + " falsely labelled as invalid");
                }
            }
            for (string iv : InvalidValues)
            {
                if (ValidCard(iv, c)) // Tests invalid Blue, Red, and Yellow cards
                {
                    throw("Valid Card test failed" + iv + " " + c + " falsely labelled as invalid");
                }
            }
        }
    }
    for (string ic : InvalidColours)
    {
        for (string iv : InvalidValues)
        {
            if (ValidCard(iv, ic)) // Tests cards invalid colours and values
            {
                throw("Valid Card test failed" + iv + " " + ic + " falsely labelled as invalid");
            }
        }
    }
    cout << "Valid Card test sucessful" << endl;
    return true;
}

bool TestMakeCard()
// Tests the make card function works for valid cards and throws an exception when an invalid card is tried
{
    Card card;
    bool error = false;
    for (string c : colours)
    {
        if (c == "Black")
        {
            for (string bv : blackvalues)
            {
                card = MakeCard(bv, c);
                if (!(card.GetColour() == c and card.GetValue() == bv))
                {
                    throw("Make Card test failed");
                }
            }
            for (string v : values)
            {
                try
                {
                    card = MakeCard(v, c);
                }
                catch (...)
                {
                    error = true;
                }
                if (!error)
                {
                    throw("Make Card test failed");
                }
            }
            for (string iv : InvalidValues)
            {
                try
                {
                    card = MakeCard(iv, c);
                }
                catch (...)
                {
                    error = true;
                }
                if (!error)
                {
                    throw("Make Card test failed");
                }
            }
        }
        else
        {
            for (string v : values)
            {
                card = MakeCard(v, c);
                if (!(card.GetColour() == c and card.GetValue() == v))
                {
                    throw("Make Card test failed");
                }
            }
            for (string bv : blackvalues)
            {
                try
                {
                    card = MakeCard(bv, c);
                }
                catch (...)
                {
                    error = true;
                }
                if (!error)
                {
                    throw("Make Card test failed");
                }
            }
            for (string iv : InvalidValues)
            {
                try
                {
                    card = MakeCard(iv, c);
                }
                catch (...)
                {
                    error = true;
                }
                if (!error)
                {
                    throw("Make Card test failed");
                }
            }
        }
    }
    for (string ic : InvalidColours)
    {
        for (string v : values)
        {
            try
            {
                card = MakeCard(v, ic);
            }
            catch (...)
            {
                error = true;
            }
            if (!error)
            {
                throw("Make Card test failed");
            }
        }
        for (string bv : blackvalues)
        {
            try
            {
                card = MakeCard(bv, ic);
            }
            catch (...)
            {
                error = true;
            }
            if (!error)
            {
                throw("Make Card test failed");
            }
        }
        for (string iv : InvalidValues)
        {
            try
            {
                card = MakeCard(iv, ic);
            }
            catch (...)
            {
                error = true;
            }
            if (!error)
            {
                throw("Make Card test failed");
            }
        }
    }
    cout << "Make Card test sucessful" << endl;
    return true;
}

bool TestPlayable()
// Tests whether the playable function acts as expected
{
    Card TestCards[5] = { MakeCard("2", "Blue"), MakeCard("+4", "Black"), MakeCard("Skip", "Green"), MakeCard("9", "Yellow"), MakeCard("1", "Red") };
    string TestData[3][2] = { {"6", "Yellow"}, {"+4", "Blue"},{"Skip", "Red"} };
    for (Card c : TestCards)
    {
        for (auto& rows : TestData)
        {
            if (!((c.Playable(rows[0], rows[1]) == (rows[0] == c.GetValue() or rows[1] == c.GetColour())) or c.GetColour() == "Black"))
            {
                throw("Playable test failed");
            }
        }
    }
    cout << "Playable test sucessful" << endl;
    return true;
}

bool RunTests()
// Runs all the tests and returns true if they are all sucessful
{
    try
    {
        TestValidCard();
        TestMakeCard();
        TestPlayable();
    }
    catch (string errormsg)
    {
        cout << errormsg << endl;
        return false;
    }
    return true;
}