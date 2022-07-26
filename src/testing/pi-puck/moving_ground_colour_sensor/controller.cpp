/**
 *
 * @author Aiden Neale <aidenneale@sky.com>
 */

#include "controller.h"
#include <argos3/core/utility/logging/argos_log.h>
CTestController::CTestController() :
  pcActuator(NULL),
  pcGround(NULL) {}

  /****************************************/
  /****************************************/

  void CTestController::Init(TConfigurationNode& t_tree) {
    pcActuator = GetActuator<CCI_PiPuckDifferentialDriveActuator>("pipuck_differential_drive");
    LOG << "[IMPORTANT] Reached Sensor Initialisation" << std::endl;
    LOG.Flush();
    pcGround = GetSensor<CCI_PiPuckGroundColourSensor>("pipuck_ground_colour");
  }

  void CTestController::ControlStep() {
    pcActuator->SetLinearVelocity(0.1, 0.1); // 10 centimeter per second forwards
    std::vector<Real> vecReadings;
    pcGround->Visit([&vecReadings] (const CCI_PiPuckGroundColourSensor::SInterface& s_interface) {
      vecReadings.emplace_back(s_interface.cColor.GetRed());
      vecReadings.emplace_back(s_interface.cColor.GetGreen());
      vecReadings.emplace_back(s_interface.cColor.GetBlue());

      std::cout << "R: " << vecReadings[0] <<
                  " G: " << vecReadings[1] <<
                  " B: " << vecReadings[2] << std::endl;
    });
  }

  /****************************************/
  /****************************************/

  REGISTER_CONTROLLER(CTestController, "test_controller");


