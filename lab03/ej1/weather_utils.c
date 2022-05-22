#include<stdio.h>
#include<stdbool.h>
#include "weather_utils.h"
#include "array_helpers.h"

int menor_temperatura_minima_historica_registrada(WeatherTable a){
	int output = 0;
	bool modificado = false;
	for(unsigned int iyear = 0; iyear < YEARS; iyear++){
		for(int imonth = 0; imonth < MONTHS; imonth++){
			for(unsigned int iday = 0; iday < DAYS; iday++){
				int act = a[iyear][imonth][iday]._min_temp;
				if(!modificado || act < output){
					output = act;
					modificado = true;
				}
			}
		}
	}
	return output;
}

void mayor_temperatura_maxima_por_anio(WeatherTable a,int output[YEARS]){
	for(unsigned int iyear = 0; iyear < YEARS; iyear++){
		bool modificado_mes = false;
		for(int imonth = 0; imonth < MONTHS; imonth++){
			for(unsigned int iday = 0; iday < DAYS; iday++){
				if(!modificado_mes){
					output[iyear] = a[iyear][imonth][iday]._max_temp;
					modificado_mes = true;
				}else if(output[iyear] < a[iyear][imonth][iday]._max_temp){
					output[iyear] = a[iyear][imonth][iday]._max_temp;
				}
			}
		}
	}
}

void mes_con_mayor_precipitacion_por_anio(WeatherTable a,int output[YEARS]){
	for(unsigned int iyear = 0; iyear < YEARS; iyear++){
		int maxi = -1;
		bool modificado = false;
		for(int imonth = 0; imonth < MONTHS; imonth++){
			int suma = 0;
			for(unsigned int iday = 0; iday < DAYS; iday++){
				suma += a[iyear][imonth][iday]._rainfall;
			}
			if(!modificado){
				maxi = suma;
				output[iyear] = imonth+1;
				modificado = true;
			}else if(maxi < suma){
				maxi = suma;
				output[iyear] = imonth+1;
			}
		}
	}
}
