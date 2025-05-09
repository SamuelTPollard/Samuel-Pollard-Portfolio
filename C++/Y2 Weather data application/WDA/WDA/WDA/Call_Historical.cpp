#include "Call_Historical.h"

Call_Historical::Call_Historical(Location _loc) : Call(_loc)
{
	Call::SetLocation(_loc);
	Call::SetSource("archive?", "archive-");
}

string Call_Historical::Decode_Param()
{
	string params;
	Call::TimeInterval(params);
	vector<string> hourlyparams = { "temperature_2m", "relative_humidity_2m", "dew_point_2m", "apparent_temperature", "precipitation", "rain", "snowfall", "snow_depth", "weather_code", "pressure_msl", "surface_pressure", "cloud_cover", "cloud_cover_low", "cloud_cover_mid", "cloud_cover_high", "et0_fao_evapotranspiration", "vapour_pressure_deficit", "wind_speed_10m", "wind_speed_100m"," wind_direction_10m", "wind_direction_100m", "wind_gusts_10m", "soil_temperature_0_to_7cm", "soil_temperature_7_to_28cm", "soil_temperature_28_to_100cm", "soil_temperature_100_to_255cm", "soil_moisture_0_to_7cm", "soil_moisture_7_to_28cm", "soil_moisture_28_to_100cm", "soil_moisture_100_to_255cm", "is_day", "sunshine_duration"};
	vector<string> radiationparams{ "shortwave_radiation", "direct_radiation", "diffuse_radiation", "direct_normal_irradiance", "global_tilted_irradiance", "terrestrial_radiation", "shortwave_radiation_instant", "direct_radiation_instant", "diffuse_radiation_instant", "direct_normal_irradiance_instant", "global_tilted_irradiance_instant", "terrestrial_radiation_instant" };
	vector<string> dailyparams = { "weather_code", "temperature_2m_max", "temperature_2m_min", "temperature_2m_mean", "apparent_temperature_max", "apparent_temperature_min", "apparent_temperature_mean", "sunrise", "sunset", "daylight_duration", "sunshine_duration", "precipitation_sum", "rain_sum", "snowfall_sum", "precipitation_hours", "wind_speed_10m_max", "wind_gusts_10m_max", "wind_direction_10m_dominant", "shortwave_radiation_sum", "et0_fao_evapotranspiration" };
	vector<string> models{ "best_match", "ecmwf_ifs", "era5_seamless", "era5", "era5_land", "cerra" };
	Call::ChooseParams(params, "&hourly=", "hourly value(s)", hourlyparams);
	Call::ChooseParams(params, ",", "hourly solar radiation value(s)", radiationparams);
	Call::ChooseParams(params, "&models=", "reanalysis model(s)", models);
	Call::ChooseParams(params, "&daily=", "daily value(s)", dailyparams);
	Call::ChooseParams(params, "&temperature_unit=", "temperature unit", { "celsius", "fahrenheit" });
	Call::ChooseParams(params, "&wind_speed_unit=", "wind speed unit", { "kmh", "ms", "mph", "kn" });
	Call::ChooseParams(params, "&precipitation_unit=", "precipitation unit", { "mm", "inch" });
	return params;
}
