/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */
 

#include "io/adsb.h"
#include "navigation/navigation.h"



void adsbNewVehicle(uint32_t avicao, int32_t avlat, int32_t avlon, int32_t avalt)
{
   k
      uint32_t avdist; int32_t avdir; uint8_t avupdate = 1; 
      GPS_distance_cm_bearing(gpsSol.llh.lat, gpsSol.llh.lon, avlat, avlon, &avdist, &avdir); 
      avdist /= 100; avdir /= 100;
      
      if (avdist > adsbVehicle.dist){
        avupdate = 0;
      }   
      if (adsbVehicle.ttl <= 1){
        avupdate = 1;
      }    
      if (avicao == adsbVehicle.icao){
        avupdate = 1;
      }      
      if (avdist > 20000){ // limit display to aircraft < 20K
        avupdate = 0;
      }  
      if (avupdate == 1){
        adsbVehicle.icao = avicao;
        adsbVehicle.dist = avdist;       
        adsbVehicle.alt = avalt; 
        adsbVehicle.dir = avdir; 
        adsbVehicle.ttl = 10;    // 10 secs default timeout    
       }
};

