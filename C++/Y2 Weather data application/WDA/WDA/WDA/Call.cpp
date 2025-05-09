#include "Call.h"

Call::Call() {};

Call::Call(Location _loc)
{
    loc = _loc;
}

string Call::Decode_Param()
{
    return "";
}

static size_t write_data(void* contents, size_t size, size_t nmemb, void* userp) // Json writing function from https://stackoverflow.com/questions/70557232/trying-to-get-a-json-output-from-curllib-in-c
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static void JsonPrint(json Json) 
{
    json values;
    for (auto it = Json.begin(); it != Json.end(); ++it) // First loop to ensure time is always the first column of the printed data
    {
        if (it.key() == "time")
        {
            cout << left << setw(25) << it.key();
            values.push_back(it.value());
        }
    }
    for (auto it = Json.begin(); it != Json.end(); ++it) // Second loop to print the rest of the data
    {
        if (it.key() != "time")
        {
            cout << left << setw(25) << it.key();
            values.push_back(it.value());
        }
    }
    cout << endl;
    int vals = values[0].size();
    int params = values.size();
    for (int i = 0; i < vals; i++)
    {
        for (int j = 0; j < params; j++)
        {
            cout << left << setw(25) << to_string(values[j][i]);
        }
        cout << endl;
    }
}

void Call::Make()
{
    CURL* disp = curl_easy_init();
    CURL* file = curl_easy_init();
    CURLcode dispres;
    CURLcode fileres;
    json Weatherjson;
    string stream, filestream;
    if (disp && file)
    {
        string timesets, format, apiname, filename;
        const vector<string> TimeZones = { "America%2FAnchorage", "America%2FLos_Angeles", "America%2FDenver", "America%2FChicago", "America%2FNew_York", "America%2FSao_Paulo", "GMT", "auto", "Europe%2FLondon", "Europe%2FBerlin", "Europe%2FMoscow", "Africa%2FCairo", "Asia%2FBangkok", "Asia%2FSingapore", "Asia%2FTokyo", "Australia%2FSydney", "Pacific%2FAuckland"};
        Call::ChooseParams(timesets, "&timeformat", "time format", { "iso8601", "unixtime" });
        ChooseParams(timesets, "&timezone", "time zone", TimeZones);
        bool valid = false;
        while (!valid)
        {
            int choice;
            valid = true;
            cout << "What file format would you like to save the data as" << endl
                << "1 - .json" << endl
                << "2 - .csv" << endl
                << "3 - .xlsx" << endl;
            cin >> choice;
            ofstream weatherdata;
            switch (choice)
            {
            case 1:
                format = "json";
                break;
            case 2:
                format = "csv";
                break;
            case 3:
                format = "xlsx";
                break;
            default:
                cout << "Invalid input" << endl;
                valid = false;
                cin.clear();
                cin.ignore();
            }
        }
        string url = "https://" + presource + "api.open-meteo.com/v1/" + source + loc.GetLocation() + timesets + Decode_Param();
        curl_easy_setopt(disp, CURLOPT_URL, url.c_str());
        curl_easy_setopt(disp, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(disp, CURLOPT_WRITEDATA, &stream);
        curl_easy_setopt(file, CURLOPT_URL, (url + "&format=" + format).c_str());
        curl_easy_setopt(file, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(file, CURLOPT_WRITEDATA, &filestream);
        dispres = curl_easy_perform(disp);
        fileres = curl_easy_perform(file);
        if (dispres != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_operation() failed : %s\n", curl_easy_strerror(dispres));
            return;
        }
        apiname = source;
        apiname.pop_back();
        filename = "ExportData\\" + loc.GetName() + apiname + "." + format;
        ofstream weatherdata(filename);
        weatherdata << filestream;
        weatherdata.close();
    }
    Weatherjson = json::parse(stream);
    curl_easy_cleanup(disp);
    if (Weatherjson.contains("error")) // Prints API message if there is missing data
    {
        cout << "API error message: " + Weatherjson.at("reason");
        return;
    }
    char print;
    bool valid = false;
    while (!valid) 
    {
        valid = true;
        cout << "Would you like to display the weather values? (y/n)" << endl;
        cin >> print;
        if (print == 'y')
        {
            if (Weatherjson.contains("hourly")) // Checks whether the json contains hourly values, printing them if there is any
            {
                cout << endl << "Hourly values" << endl;
                JsonPrint(Weatherjson.at("hourly"));
            }
            if (Weatherjson.contains("daily")) // Checks whether the json contains daily values, printing them if there is any
            {
                cout << endl << "Daily values" << endl;
                JsonPrint(Weatherjson.at("daily"));
            }
        }
        else if (print == 'n') {}
        else
        {
            cout << "Invalid choice" << endl;
            valid = false;
        }
    }
    valid = false;
}

Location Call::GetLoc(string locname)
{
    stringstream locName = (stringstream)locname;
    locname.clear();
    json locjson;
    string locParts;
    while (getline(locName, locParts, ' '))
    {
        locname += locParts + "+";
    }
    locname.pop_back();
    CURL* req = curl_easy_init(); 
    CURLcode res;
    bool valid = false;
    if (req)
    {
        while (!valid)
        {
            valid = true;
            string stream;
            string url = "https://geocoding-api.open-meteo.com/v1/search?name=" + locname + "&count=10&language=en&format=json";
            curl_easy_setopt(req, CURLOPT_URL, url.c_str());
            curl_easy_setopt(req, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(req, CURLOPT_WRITEDATA, &stream);
            res = curl_easy_perform(req);
            if (res != CURLE_OK)
            {
                fprintf(stderr, "curl_easy_operation() failed : %s\n", curl_easy_strerror(res));
            }
            else
            {
                locjson = json::parse(stream);
                try { locjson.at("results"); }
                catch (...)
                {
                    valid = false;
                    cout << "No locations found, please enter a new location name: ";
                    cin >> locname;
                }
            }
        }
    }
    curl_easy_cleanup(req);
    vector<Location> foundlocs;
    int count = 1, choice;
    valid = false;
    while (!valid)
    {
        valid = true;
        cout << "Locations found for \"" << locname << "\"" << endl;
        for (json j : locjson.at("results"))
        {
            foundlocs.push_back(Location(j.at("admin1_id"), j.at("name"), j.at("latitude"), j.at("longitude")));
            cout << to_string(count) << " " << (string)j.at("name") << ", " << (string)j.at("country") << endl;
            count++;
        }
        cout << "Enter location number from above list: " << endl;
        cin >> choice;
        if (choice < 0 || choice > count - 1)
        {
            cout << "Invalid choice" << endl;
            valid = false;
            cin.clear();
            cin.ignore();
            count = 1;
        }
    }
    return foundlocs[choice - 1];
}

void Call::SetLocation(Location _loc)
{
    loc = _loc;
}

void Call::SetSource(string _source, string _presource)
{
    presource = _presource;
    source = _source;
}

void Call::ChooseParams(string& params, string tail, string name, vector<string> paramsvec)
{
    string choice, adstring;
    adstring += tail;
    cout << "Enter numbers for desired " + name + " seperated by commas, or type \'0\' for none." << endl;
    for (int i = 0; i < paramsvec.size(); i++)
    {
        cout << (i + 1) << " " << paramsvec[i] << (((i + 1) % 3 == 0) ? '\n' : '\t');
    }
    cout << endl;
    cin >> choice;
    stringstream dstream = (stringstream)choice;
    try
    {
        string nums;
        while (getline(dstream, nums, ','))
        {
            if (nums == "") { continue; }
            if (stoi(nums) == 0) { return; }
            if ((stoi(nums) - 1) <= paramsvec.size())
            {
                adstring += (paramsvec[stoi(nums) - 1]) + ",";
            }
        }
    }
    catch(exception e)
    {
        return;
    }
    adstring.pop_back(); // removing extra comma
    params += adstring; 
}

void Call::TimeType(string& params)
{
    bool valid = false;
    while (!valid)
    {
        valid = true;
        int choice;
        cout << "Choose period type: " << endl
            << "1 - Forecast length" << endl
            << "2 - Time interval" << endl;
        cin >> choice;
        if (choice == 1)
        {
            Forecastlength(params);
        }
        else if (choice == 2)
        {
            TimeInterval(params);
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

void Call::Forecastlength(string& params)
{
    bool valid = false;
    while (!valid)
    {
        int fdays;
        cout << "Enter forecast days (betweeen 1 and 16): ";
        cin >> fdays;
        if (fdays >= 1 && fdays <= 16)
        {
            valid = true;
            params += "&forcast_days=" + to_string(fdays);
        }
        else
        {
            cout << "\nInvalid forecast days\n";
            cin.clear();
            cin.ignore();
        }
    }
    valid = false;
    while (!valid)
    {
        int pdays;
        cout << "Enter past days (betweeen 0 and 92): ";
        cin >> pdays;
        if (pdays >= 0 && pdays <= 92)
        {
            valid = true;
            params += "&past_days=" + to_string(pdays);
        }
        else
        {
            cout << "\nInvalid past days\n";
            cin.clear();
            cin.ignore();
        }
    }
}

bool ValidDate(string date)
{
    vector<int> Split = SplitDate(date);
    if (Split.size() != 3) { return false; }
    int year = Split[0], month = Split[1], day = Split[2];
    if (year < 1940 || year > 9999)
    {
        return false;
    }
    if (month < 0 || month > 12)
    {
        return false;
    }
    if (day < 1 || day > 31)
    {
        return false;
    }
    if ((day == 4 || day == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29)
                return false;
        }
        else {
            if (day > 28)
                return false;
        }
    }
    return true;
}

bool DateAfter(string sdate, string edate)
{
    vector<int> Sdate = SplitDate(sdate);
    vector<int> Edate = SplitDate(edate);
    for (int i = 0; i < 3; i++)
    {
        if (Sdate[i] > Edate[i])
        {
            return false;
        }
    }
    return true;
}

vector<int> SplitDate(string date)
{
    stringstream sstream = (stringstream)date;
    string split;
    vector<int> v = {};
    while (getline(sstream, split, '-'))
    {
        v.push_back(stoi(split));
    }
    return v;
}

void Call::TimeInterval(string& params)
{
    params += "&time_mode=time_interval";
    bool valid = false;
    string sdate;
    while (!valid)
    {
        cout << "Enter start date (yyyy-mm-dd): ";
        cin >> sdate;
        if (ValidDate(sdate))
        {
            valid = true;
            params += "&start_date=" + sdate;
        }
        else
        {
            cout << "\nInvalid date\n";
        }
    }
    valid = false;
    while (!valid)
    {
        string edate;
        cout << "Enter end date (yyyy-mm-dd): ";
        cin >> edate;
        if (ValidDate(edate) && DateAfter(sdate, edate))
        {
            valid = true;
            params += "&end_date=" + edate;
        }
        else
        {
            cout << "\nInvalid date\n";
        }
    }
}
