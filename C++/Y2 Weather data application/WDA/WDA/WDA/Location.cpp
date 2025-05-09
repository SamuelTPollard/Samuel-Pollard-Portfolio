#include "Location.h"

Location::Location(int _id, string _name, float _latitude, float _longitude)
{
		Location_ID = _id;
		Location_name = _name;
		Latitude = _latitude;
		Longitude = _longitude;
		Favourite = false;
}

void Location::SetId(int _id)
{
	Location_ID = _id;
}

void Location::SetName(vector<Location> locations)
{
	bool valid = false;
	string locationname;
	while (!valid)
	{
		valid = true;
		cout << "Enter location name: ";
		string name;
		getline(cin, name);
		if (name == "" || name == " ") 
		{
			cout << "Locaiton name can't be blank" << endl;
			valid = false;
		}
		for (Location l : locations)
		{
			if (name == l.GetName())
			{
				cout << "Location name already exists" << endl;
				valid = false;
			}
		}
		locationname = name;
	}
	Location_name = locationname;
}

void Location::SetLocation(vector<Location> locations)
{
	bool valid = false;
	float latitude, longitude;
	while (!valid)
	{
		valid = true;
		cout << "Enter latitude: ";
		cin >> latitude;
		cout << "Enter longitude: ";
		cin >> longitude;
		if (!(latitude >= -90 && latitude <= 90 && longitude >= -180 && longitude <= 180))
		{
			cout << "Invalid latitude or longitude value. Latitude must be between -90 and 90, longitude must be between -180 and 180" << endl;
			valid = false;
			cin.clear();
			cin.ignore();
		}
	}
	Latitude = latitude;
	Longitude = longitude;
}

void Location::SetFavourite(bool _favourite)
{
	Favourite = _favourite;
}

void Location::Save()
{
	ofstream LocFile("Locations.txt", ios::app);
	LocFile << To_String() << endl;
	LocFile.close();
}

void Load(vector<Location>& locations)
{
	ifstream LocFile("Locations.txt");
	string LocText, Splitloc;
	while (getline(LocFile, LocText))
	{
		vector<string> LocParams;
		stringstream sstream = (stringstream)LocText;
		while (getline(sstream, Splitloc, ','))
		{
			LocParams.push_back(Splitloc);
		}
		locations.push_back(Location(stoi(LocParams[0]), LocParams[1], stof(LocParams[2]), stof(LocParams[3])));
		if (LocParams.size() == 5)
		{
			locations[locations.size() - 1].SetFavourite(true);
		}
		
	}
	
	LocFile.close();
}

void ReloadFile(vector<Location> locations)
{
	ofstream LocFile("Locations.txt");
	LocFile.clear();
	for (int i  = 0 ; i < locations.size() ; i++)
	{
		locations[i].SetId(i + 1);
		locations[i].Save();
	}
	LocFile.close();
	Load(locations);
}

Location Find(int ID, vector<Location> locations)
{
	bool found = false;
	while (!false)
	{
		for (Location l : locations)
		{
			if (l.GetId() == ID)
			{
				return l;
			}
		}
		return Location(); 
	}
}

vector<Location> FindName(string name, vector<Location> locations)
{
	vector<Location> foundlocs;
	for (Location l : locations)
	{
		if (l.GetName().find(name) != string::npos) // Finds whether the string name is in the string location.name
		{
			foundlocs.push_back(l);
		}
	}
	return foundlocs;
}