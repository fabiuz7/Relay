/***************************************************************************
 *   Copyright (C) 2018, 2019 by Fabiano Riccardi                          *
 *                                                                         *
 *   This file is part of Dimmable Light for Arduino                       *
 *                                                                         *
 *   Dimmable Light for Arduino is free software; you can redistribute     *
 *   it and/or modify it under the terms of the GNU Lesser General Public  *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/
#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#if defined(ESP8266) || defined(ESP32)
#include <unordered_map>
#elif defined(AVR)
#include <ArduinoSTL.h>
#include <map>
#endif

#include "Relay.h"

/**
 * Class to store the mapping between a DimmableLight object and 
 * a (friendly) name. This could be useful when developing APIs.
 */
class RelayManager{
public:
  
  /**
   * Create a new light with a given name
   */
  bool add(String lightName, uint8_t pin, bool normallyOpen = false);

  /**
   * Get a light with a specific name, if any
   */
  Relay* get(String lightName);

  /**
   * Get a light from from the contaniner.
   * 
   * This method is "circular", that means once you get the last element
   * the nect call return the first one.
   */
  std::pair<String, Relay*> get();

  int getCount(){
    return dla.size();
  }
  
private:
#if defined(ESP8266) || defined(ESP32)
  std::unordered_map<std::string, Relay*> dla;
#elif defined(AVR)
  std::map<std::string, Relay*> dla;
#endif
};

#endif // END RELAY_MANAGER_H
