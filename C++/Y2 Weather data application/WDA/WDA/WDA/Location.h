#pragma once
#include "Header.h"

class Location
{
private:
	int Location_ID;
	string Location_name;
	float Latitude, Longitude;
	bool Favourite;

public:

	Location(int _id, string _name, float _latitude, float _longitude);

	Location() = default;

	int GetId() const { return Location_ID; } 

	void SetId(int _id);

	string GetName() const { return Location_name; }

	void SetName(vector<Location> locations);

	string GetLocation() const { return "&latitude=" + to_string(Latitude) + "&longitude=" + to_string(Longitude); }

	void SetLocation(vector<Location> locations);

	string To_String() const { return to_string(Location_ID) + "," + Location_name + "," + to_string(Latitude) + "," + to_string(Longitude) + (Favourite ? ",*" : ""); }

	bool IsFavourite() const { return Favourite; }

	void SetFavourite(bool _favourite);

	void Save();

};

void Load(vector<Location>& locations);

void ReloadFile(vector<Location> locations);

Location Find(int ID, vector<Location> locations);

vector<Location> FindName(string name, vector<Location> locations);

