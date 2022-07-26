/**
 * @file <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_ground_colour_sensor.cpp>
 *
 * @author Aiden Neale - <arn519@york.ac.uk>
 */

#include "ci_pipuck_ground_colour_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
  void CCI_PiPuckGroundColourSensor::CreateLuaState(lua_State* pt_lua_state) {
//     CLuaUtility::StartTable(pt_lua_state, "ground_colour_sensors");
//     Visit([pt_lua_state] (const SInterface& s_interface) {
//         CLuaUtility::StartTable(pt_lua_state, s_interface.Label + 1);
//         CLuaUtility::AddToTable(pt_lua_state, "color", s_interface.cColor);
//         CLuaUtility::StartTable(pt_lua_state, "transform");
//         CLuaUtility::AddToTable(pt_lua_state, "position", std::get<CVector3>(s_interface.Configuration));
//         CLuaUtility::AddToTable(pt_lua_state, "orientation", std::get<CQuaternion>(s_interface.Configuration));
//         CLuaUtility::AddToTable(pt_lua_state, "anchor", std::get<std::string>(s_interface.Configuration));
//         CLuaUtility::EndTable(pt_lua_state);
//         CLuaUtility::EndTable(pt_lua_state);
//     });
//     CLuaUtility::EndTable(pt_lua_state);
  }
#endif

  /****************************************/
  /****************************************/

#ifdef ARGOS_WITH_LUA
  void CCI_PiPuckGroundColourSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
//     lua_getfield(pt_lua_state, -1, "ground_colour_sensors");
//     Visit([pt_lua_state] (const SInterface& s_interface) {
//         lua_pushnumber(pt_lua_state, s_interface.Label + 1);
//         lua_gettable(pt_lua_state, -2);
//         lua_pushstring(pt_lua_state, "Color");
//         lua_pushnumber(pt_lua_state, s_interface.cColor);
//         lua_settable(pt_lua_state, -3);
//         lua_pop(pt_lua_state, 1);
//     });
//     lua_pop(pt_lua_state, 1);
  }
#endif

  /****************************************/
  /****************************************/

  const std::map<UInt8, CCI_PiPuckGroundColourSensor::TConfiguration> CCI_PiPuckGroundColourSensor::MAP_SENSOR_CONFIG = {
    std::make_pair(0, std::make_tuple("origin", CVector3(0.03,  0.01, 0.002), CQuaternion(CRadians::PI, CVector3::Y), 0.005)),
    std::make_pair(1, std::make_tuple("origin", CVector3(0.03,  0.0,  0.002), CQuaternion(CRadians::PI, CVector3::Y), 0.005)),
    std::make_pair(2, std::make_tuple("origin", CVector3(0.03, -0.01, 0.002), CQuaternion(CRadians::PI, CVector3::Y), 0.005)),
  };

  /****************************************/
  /****************************************/


}
