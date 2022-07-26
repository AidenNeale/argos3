/**
 * @file <argos3/plugins/robots/pi-puck/simulator/pipuck_ground_default_colour_sensor.cpp>
 *
 * @author Aiden Neale - <arn519@york.ac.uk>
 */

#include <argos3/core/utility/math/plane.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/floor_entity.h>

#include "pipuck_ground_default_colour_sensor.h"

namespace argos {

  /****************************************/
  /****************************************/

  CPiPuckGroundDefaultColourSensor::CPiPuckGroundDefaultColourSensor() :
    m_bShowRays(false),
    m_pcControllableEntity(nullptr),
    m_cFloorEntity(CSimulator::GetInstance().GetSpace().GetFloorEntity()) {}

  /****************************************/
  /****************************************/

  void CPiPuckGroundDefaultColourSensor::SetRobot(CComposableEntity& c_entity) {
    m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
    /* allocate memory for the sensor interfaces */
    m_vecSimulatedInterfaces.reserve(MAP_SENSOR_CONFIG.size());
    /* get the anchors for the sensor interfaces from m_mapSensorConfig */
    for(const std::pair<const UInt8, TConfiguration>& t_config : MAP_SENSOR_CONFIG) {
        const std::string& strAnchor = std::get<std::string>(t_config.second);
        SAnchor& sAnchor =
          c_entity.GetComponent<CEmbodiedEntity>("body").GetAnchor(strAnchor);
        m_vecSimulatedInterfaces.emplace_back(t_config.first, sAnchor);
    }
  }

  /****************************************/
  /****************************************/

  void CPiPuckGroundDefaultColourSensor::Init(TConfigurationNode& t_tree) {
    try {
      CCI_PiPuckGroundColourSensor::Init(t_tree);
      GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
    }
    catch(CARGoSException& ex) {
        THROW_ARGOSEXCEPTION_NESTED("Initialization error in Pi-Puck ground colour sensor", ex);
    }
  }

  /****************************************/
  /****************************************/

  void CPiPuckGroundDefaultColourSensor::Update() {
    CVector3 cRayStart, cRayEnd, cIntersection;
    CRay3 cSensorRay;
    /* go through the sensors */
    for(SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
        cRayStart = std::get<CVector3>(s_interface.Configuration);
        cRayStart.Rotate(s_interface.Anchor.Orientation);
        cRayStart += s_interface.Anchor.Position;
        cRayEnd = CVector3::Z * std::get<Real>(s_interface.Configuration);
        cRayEnd.Rotate(std::get<CQuaternion>(s_interface.Configuration));
        cRayEnd.Rotate(s_interface.Anchor.Orientation);
        cRayEnd += cRayStart;
        cSensorRay.Set(cRayStart, cRayEnd);
        bool bIntersection = cSensorRay.Intersects(m_cFloor, cIntersection);
        if(m_bShowRays) {
          m_pcControllableEntity->GetCheckedRays().emplace_back(bIntersection, cSensorRay);
        }
        if(bIntersection) {
          /* get the color */
          s_interface.cColor =
              m_cFloorEntity.GetColorAtPoint(cIntersection.GetX(), cIntersection.GetY());
        }
        else {
          s_interface.cColor.Set("white");
        }
    }
  }

  /****************************************/
  /****************************************/

  void CPiPuckGroundDefaultColourSensor::Reset() {
    for(SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
      s_interface.cColor.Set("white");
    }
  }

  /****************************************/
  /****************************************/

  void CPiPuckGroundDefaultColourSensor::Visit(std::function<void(const SInterface&)> fn_visitor) {
    for(const SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
        fn_visitor(s_interface);
    }
  }

  /****************************************/
  /****************************************/

  const CPlane CPiPuckGroundDefaultColourSensor::m_cFloor(CVector3::ZERO, CVector3::Z);

  /****************************************/
  /****************************************/

  REGISTER_SENSOR(CPiPuckGroundDefaultColourSensor,
                  "pipuck_ground_colour", "default",
                  "Aiden Neale [arn519@york.ac.uk]",
                  "1.0",
                  "The Pi-Puck ground colour sensor.",
                  "The documentation for this sensor is currently unavailable",
                  "Usable"
  );

  /****************************************/
  /****************************************/

}
