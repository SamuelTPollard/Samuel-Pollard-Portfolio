#include "Call_AirQuality.h"

Call_AirQuality::Call_AirQuality(Location _loc) : Call(_loc)
{
	Call::SetLocation(_loc);
	Call::SetSource("air-quality?", "air-quality-");
}

string Call_AirQuality::Decode_Param()
{
	string params;
	vector<string> hourlyparams{ "pm10", "pm2_5", "carbon_monoxide", "nitrogen_dioxide", "sulphur_dioxide", "ozone", "aerosol_optical_depth", "dust", "uv_index", "uv_index_clear_sky", "ammonia", "alder_pollen", "birch_pollen", "grass_pollen", "mugwort_pollen", "olive_pollen", "ragweed_pollen"};
	vector<string> european = { "european_aqi", "european_aqi_pm2_5", "european_aqi_pm10", "european_aqi_nitrogen_dioxide", "european_aqi_ozone", "european_aqi_sulphur_dioxide" };
	Call::TimeType(params);
	Call::ChooseParams(params, "&hourly=", "hourly air quality value(s)", hourlyparams);
	Call::ChooseParams(params, ",", "european hourly air quality value(s)", european);
	Call::ChooseParams(params, "&domains=", "domain", { "auto", "cams_global", "cams_europe" });
	return params;
}
