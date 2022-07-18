/**
 *
 * @author Aiden Neale <aidenneale@sky.com>
 */

#include "controller.h"

CTestController::CTestController() :
  pcActuator(NULL) {}

  /****************************************/
  /****************************************/

  void CTestController::Init(TConfigurationNode& t_tree) {
    pcActuator = GetActuator<CCI_PiPuckDifferentialDriveActuator>("pipuck_differential_drive");
  }

  void CTestController::ControlStep() {
    pcActuator->SetLinearVelocity(0.1, 0.1); // 10 centimeter per second forwards
  }

  /****************************************/
  /****************************************/

  REGISTER_CONTROLLER(CTestController, "test_controller");


