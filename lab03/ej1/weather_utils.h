#ifndef _WEATHER_UTILS_
	#define _WEATHER_UTILS_
	
	#include<stdio.h>
	#include "array_helpers.h"
	
	int menor_temperatura_minima_historica_registrada(WeatherTable a);
	void mayor_temperatura_maxima_por_anio(WeatherTable a,int output[]);
	void mes_con_mayor_precipitacion_por_anio(WeatherTable a,int output[]);
	
#endif
