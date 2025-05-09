#include "Call_AirQuality.h"
#include "Call_Forecast.h"
#include "Call_Historical.h"

vector<Location> locations;

void PrintLocations()
{
    for (Location l : locations)
    {
        cout << l.To_String() << endl;
    }
}

Location SearchLocation()
{
    bool found = false, valid = false;
    Location loc;
    while (!valid)
    {
        valid = true;
        PrintLocations();
        int choice;
        cout << "Search option" << endl
            << "1 - Search by ID" << endl
            << "2 - Search by name" << endl;
        cin >> choice;
        if (choice == 1)
        {
            int LocID;
            while (!found)
            {
                cout << "Please enter location ID" << endl;
                found = true;
                cin >> LocID;
                if (Find(LocID, locations).GetName() == "")
                {
                    cout << "Location ID not found" << endl;
                    found = false;
                    cin.clear();
                    cin.ignore();
                }
            }
            loc = Find(LocID, locations);
        }
        else if (choice == 2)
        {
            string LocName;
            while (!found)
            {
                cout << "Please enter location name" << endl;
                found = true;
                cin >> LocName;
                vector<Location> foundlocs = FindName(LocName, locations);
                if (foundlocs.size() == 0)
                {
                    found = false;
                    cout << "No locations found" << endl;
                }
                else if (foundlocs.size() == 1)
                {
                    loc = foundlocs[0];
                }
                else
                {
                    bool valid = false;
                    int choice;
                    while (!valid)
                    {
                        cout << "Enter ID of desired location" << endl;
                        for (Location l : foundlocs) { cout << l.To_String() << endl; }
                        cin >> choice;
                        for (Location l : foundlocs) 
                        {
                            if (choice == l.GetId())
                            {
                                loc = l;
                                valid = true;
                            }
                        }
                        if (!valid) 
                        { 
                            cout << "Invalid location ID"; 
                            valid = false;
                        }
                        cin.clear();
                        cin.ignore();
                    }
                }
            }
        }
        else
        {
            cout << "Invalid option" << endl;
            valid = false;
            cin.clear();
            cin.ignore();
        }
    }
    cout << loc.To_String() << endl;
    return loc;
}

void AddLocation()
{
    int choice;
    bool valid = false;
    while (!valid)
    {
        valid = true;
        cout << "Would you like to:" << endl
            << "1 - Manually enter location data" << endl
            << "2 - Find location from API" << endl;
        cin >> choice;
        if (choice == 1)
        {
            Location MyLoc(locations.size() + 1, "", 181, 181);
            MyLoc.SetName(locations);
            MyLoc.SetLocation(locations);
            locations.push_back(MyLoc);
            MyLoc.Save();
        }
        else if (choice == 2)
        {
            vector<Location> lv;
            cout << "Please enter location name: ";
            cin.ignore();
            string Locname;
            getline(cin, Locname);
            Location loc;
            loc = Call().GetLoc(Locname);
            loc.SetId(locations.size() + 1);
            locations.push_back(loc);
            ReloadFile(locations);
            if (lv.size() == 1)
            {
                loc = lv[0];
            }
        }
        else
        {
            cout << "Invalid input" << endl;
            valid = false;
            cin.clear();
            cin.ignore();
        }
    }

}

void EditLocation(int locnum)
{
    int choice;
    bool valid = false;
    while (!valid)
    {
        valid = true;
        cout << "Choose edit option" << endl
            << "1 - Change name" << endl
            << "2 - Change latitude and longitude" << endl;
        cin >> choice;
        if (choice == 1)
        {
            locations[locnum].SetName(locations);
        }
        else if (choice == 2)
        {
            locations[locnum].SetLocation(locations);
        }
        else
        {
            valid = false;
            cin.clear();
            cin.ignore();
        }
    }
    ReloadFile(locations);
} 

void ModifyLocations()
{
    bool valid = false;
    Location loc;
    loc = SearchLocation();
    int locnum;
    for (int i = 0; i < locations.size(); i++) {
        if (locations[i].To_String() == loc.To_String()) {
            locnum = i;
        }
    }
    while (!valid)
    {
        valid = true;
        int choice;
        cout << "Location modification " << endl
            << "1 - Delete a location" << endl
            << "2 - Modifiy location" << endl
            << "3 - Toggle favourite" << endl;
        cin >> choice;
        if (choice == 1)
        {
            int pos = 0;
            for (int i = 0; i < locations.size(); i++) { if (locations[i].To_String() == loc.To_String()) { pos = i; break; } }
            locations.erase(locations.begin() + pos);
        }
        else if (choice == 2)
        {
            EditLocation(locnum);
        }
        else if (choice == 3)
        {
            locations[locnum].SetFavourite(!locations[locnum].IsFavourite());
            ReloadFile(locations);
        }
        else
        {
            cout << "Invalid choice" << endl;
            cin.clear();
            cin.ignore();
            valid = false;
        }
    }
}


void WeatherData()
{
    bool valid = false;
    int choice;
    Location MyLoc;
    if (locations.size() == 0)
    {
        AddLocation();
    }
    MyLoc = SearchLocation();
    valid = false;
    while (!valid)
    {
        valid = true;
        cout << "Choose weather data source" << endl
            << "1 - Weather Forcast" << endl
            << "2 - Historical Weather" << endl
            << "3 - Air quality" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            Call_Forecast(MyLoc).Make();
            break;
        case 2:
            Call_Historical(MyLoc).Make();
            break;
        case 3:
            Call_AirQuality(MyLoc).Make();
            break;
        default:
            cout << "Invalid choice";
            cin.clear();
            cin.ignore();
            valid = false;
            break;
        }
    }
}

void LocationManagement()
{
    bool valid = false;
    int choice;
    while (!valid)
    {
        cout << "Location management" << endl
            << "1 - Add new location" << endl
            << "2 - List locations" << endl
            << "3 - Modify Location data" << endl
            << "4 - Search for location" << endl
            << "5 - Main menu" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            AddLocation();
            break;
        case 2:
            PrintLocations();
            break;
        case 3:
            ModifyLocations();
            break;
        case 4:
            SearchLocation();
            break;
        case 5:
            valid = true;
            break;
        default:
            cout << "invalid option";
            cin.clear();
            cin.ignore();
        }
    }

}

bool MainMenu()
{
    bool valid = false;
    int choice;
    while (!valid)
    {
        valid = true;
        cout << "Main menu" << endl
            << "1 - Location Management" << endl
            << "2 - Weather data" << endl
            << "3 - Quit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            LocationManagement();
            break;
        case 2:
            WeatherData();
            break;

        case 3:
            return false;
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice" << endl;
            cin.clear();
            cin.ignore();
            valid = false;
        };
    }
    return true;
}

int main(int argc, char* argv[])
{
    Load(locations);
    while (MainMenu()) {};
    return 0;
}
