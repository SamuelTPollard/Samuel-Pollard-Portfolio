#include "Call_Forecast.h"

Call_Forecast::Call_Forecast(Location _loc) : Call(_loc)
{
	Call::SetLocation(_loc);
	Call::SetSource("forecast?", "");
}

static vector<string> pparams()
{
	vector<string> params;
	for (string s : vector<string>{ "temperature", "relative_humidity", "cloud_cover", "windspeed", "winddirection", "geopotential_height" })
	{
		for (string s2 : vector<string>{ "_1000hPa", "_975hPa", "_950hPa", "_925hPa", "_900hPa", "_850hPa", " _800hPa", "_700hPa", "_600hPa", " _500hPa", "_400hPa", "_300hPa", "_250hPa", "_200hPa", "_150hPa", "_100hPa", "_70hPa", "_50hPa", "_30hPa" })
		{
			params.push_back(s + s2);
		}
	}
	return params;
}

string Call_Forecast::Decode_Param()
{
	string params;
	const vector<string> hourlyparams = { "temperature_2m", "relative_humidity_2m", "dew_point_2m", "apparent_temperature", "precipitation_probability", "precipitation", "rain", "showers", "snowfall", "snow_depth", "weather_code", "pressure_msl", "surface_pressure", "cloud_cover", "cloud_cover_low", "cloud_cover_mid", "cloud_cover_high", "visibility", "evapotranspiration", "et0_fao_evapotranspiration", "vapour_pressure_deficit", "wind_speed_10m", "wind_speed_80m", "wind_speed_120m", "wind_speed_180m", "wind_direction_10m", "wind_direction_80m", "wind_direction_120m", "wind_direction_180m", "wind_gusts_10m", "temperature_80m", "temperature_120m", "temperature_180m", "soil_temperature_0cm", "soil_temperature_6cm", "soil_temperature_18cm", "soil_temperature_54cm", "soil_moisture_0_to_1cm", "soil_moisture_1_to_3cm", "soil_moisture_3_to_9cm", "soil_moisture_9_to_27cm", "soil_moisture_27_to_81cm", "uv_index", "uv_index_clear_sky", "is_day", "cape", "freezing_level_height", "sunshine_duration"};
	vector<string> radiationparams{ "shortwave_radiation", "direct_radiation", "diffuse_radiation", "direct_normal_irradiance", "global_tilted_irradiance", "terrestrial_radiation", "shortwave_radiation_instant", "direct_radiation_instant", "diffuse_radiation_instant", "direct_normal_irradiance_instant", "global_tilted_irradiance_instant", "terrestrial_radiation_instant" };
	const vector<string> weathermodels = { "best_match", "ecmwf_ifs04", "ecmwf_ifs025", "ecmwf_aifs025", "cma_grapes_global", "bom_access_global", "metno_nordic", "gfs_seamless", "gfs_global", "gfs_hrrr", "jma_seamless", "jma_msm", "jma_gsm", "icon_seamless", "icon_global", "icon_eu", "icon_d2", "gem_seamless", "gem_global", "gem_regional", "gem_hrdps_continental", "meteofrance_seamless", "meteofrance_arpege_world", "meteofrance_arpege_europe", "meteofrance_arome_france", "meteofrance_arome_france_hd", "arpae_cosmo_seamless", "arpae_cosmo_2i", "arpae_cosmo_2i_ruc", "arpae_cosmo_5m" };
	const vector<string> dailyparams = { "weather_code", "temperature_2m_max", "temperature_2m_min", "apparent_temperature_max", "apparent_temperature_min", "sunrise", "sunset", "daylight_duration", "sunshine_duration", "uv_index_max", "uv_index_clear_sky_max", "precipitation_sum", "rain_sum", "showers_sum", "snowfall_sum", "precipitation_hours", "precipitation_probability_max", "wind_speed_10m_max", "wind_gusts_10m_max", "wind_direction_10m_dominant", "shortwave_radiation_sum", "et0_fao_evapotranspiration" };
	// Choosing whether the user wants to use forecasts days or a time interval
	Call::TimeType(params);
	// Houry parameters;
	Call::ChooseParams(params, "&hourly=", "hourly value(s)", hourlyparams);
	Call::ChooseParams(params, ",", "hourly solar radiation value(s)", radiationparams);
	// Pressure params
	Call::ChooseParams(params, ",", "hourly pressure level value(s)", pparams());
	// Weather models
	Call::ChooseParams(params, "&models=", "weather model(s)", weathermodels);
	// Daily vaues
	Call::ChooseParams(params, "&daily=", "daily value", dailyparams);
	Call::ChooseParams(params, "&temperature_unit=", "temperature unit", { "celsius", "fahrenheit" });
	Call::ChooseParams(params, "&wind_speed_unit=", "wind speed unit", { "kmh", "ms", "mph", "kn" });
	Call::ChooseParams(params, "&precipitation_unit=", "precipitation unit", { "mm", "inch" });
	return params;
}
