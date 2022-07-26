/**
 * @file <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_ground_colour_sensor.h>
 *
 * @author Aiden Neale - <arn519@york.ac.uk>
 */

#ifndef CCI_PIPUCK_GROUND_COLOUR_SENSOR_H
#define CCI_PIPUCK_GROUND_COLOUR_SENSOR_H

namespace argos {
   class CCI_PiPuckGroundColourSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>
#include <argos3/core/utility/datatypes/color.h>

#include <map>
#include <tuple>
#include <functional>

namespace argos {

   class CCI_PiPuckGroundColourSensor : public CCI_Sensor {

   public:

      using TConfiguration = std::tuple<std::string, CVector3, CQuaternion, Real>;

      struct SInterface {
         /* constructor */
         SInterface(UInt8 un_label) :
            Label(un_label),
            Configuration(MAP_SENSOR_CONFIG.at(un_label)),
            cColor(CColor::WHITE) {}
         /* members */
         const UInt8 Label;
         const TConfiguration& Configuration;
         CColor cColor;
      };

   public:

      virtual ~CCI_PiPuckGroundColourSensor() {}

      virtual void Visit(std::function<void(const SInterface&)>) = 0;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      static const std::map<UInt8, TConfiguration> MAP_SENSOR_CONFIG;

   };

}

#endif
