/**
 *
 * @author Aiden Neale <arn519@york.ac.uk>
 */

#ifndef PIPUCK_GROUND_COLOUR_SENSOR_TEST_H
#define PIPUCK_GROUND_COLOUR_SENSOR_TEST_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_differential_drive_actuator.h>
#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_ground_colour_sensor.h>

using namespace argos;

  class CTestController : public CCI_Controller {

  public:
    /* Class Constructor */
    CTestController();

    /* Class Destructor */
    virtual ~CTestController() {}

    virtual void Init(TConfigurationNode& t_tree);
    virtual void ControlStep();
    virtual void Reset() {}
    virtual void Destroy() {}


  private:
    /* Pointer to the differential drive actuator */
    CCI_PiPuckDifferentialDriveActuator* pcActuator;
    CCI_PiPuckGroundColourSensor* pcGround;
  };


#endif