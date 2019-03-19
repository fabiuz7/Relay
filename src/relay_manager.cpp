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
#include "relay_manager.h"

bool RelayManager::add(String lightName, uint8_t pin, bool normallyOpen){
  const char* temp=lightName.c_str();
#if defined(ESP8266) || defined(ESP32)
  std::unordered_map<std::string, Relay*>::const_iterator it=dla.find(temp);
#elif defined(AVR)
  std::map<std::string, Relay*>::const_iterator it=dla.find(temp);
#endif
  if(it==dla.end()){
    Relay* pRelay=new Relay(pin, normallyOpen);
    dla.insert({lightName.c_str(), pRelay});
    return true;
  }else{
    return false;
  }
}

Relay* RelayManager::get(String lightName){
  const char* temp=lightName.c_str();
#if defined(ESP8266) || defined(ESP32)
  std::unordered_map<std::string, Relay*>::const_iterator it=dla.find(temp);
#elif defined(AVR)
  std::map<std::string, Relay*>::const_iterator it=dla.find(temp);
#endif
  if(it!=dla.end()){
    return it->second;
  }else{
    return nullptr;
   }
}

std::pair<String, Relay*> RelayManager::get(){
#if defined(ESP8266) || defined(ESP32)
  static std::unordered_map<std::string, Relay*>::const_iterator it=dla.begin();
#elif defined(AVR)
  static std::map<std::string, Relay*>::const_iterator it=dla.begin();
#endif
  String name=it->first.c_str();
  std::pair<String, Relay*> res(name, it->second);

  it++;
  if(it==dla.end()){
    it=dla.begin();
  }
  return res;
}
