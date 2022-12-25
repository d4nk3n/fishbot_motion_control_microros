#ifndef __FISHBOT_H__
#define __FISHBOT_H__
/* ESP32 */
#include <WiFi.h>
#include <Esp32PcntEncoder.h>
#include <Esp32McpwmMotor.h>
#include <PidController.h>
#include <Kinematics.h>

/* MicroROS */
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rclc_parameter/rclc_parameter.h>
#include <nav_msgs/msg/odometry.h>
#include <geometry_msgs/msg/twist.h>
#include <fishbot_interfaces/srv/fish_bot_config.h>
#include <micro_ros_utilities/type_utilities.h>

#include "micro_ros_transport_serial.h"
#include "micro_ros_transport_wifi_udp.h"

#include "fishlog.h"
#include "fishbot_config.h"

#define RCSOFTCHECK(fn)                                                                 \
    {                                                                                   \
        rcl_ret_t temp_rc = fn;                                                         \
        if ((temp_rc != RCL_RET_OK))                                                    \
        {                                                                               \
            printf(                                                                     \
                "Failed status on line %d: %d. Continuing.\n", __LINE__, (int)temp_rc); \
        }                                                                               \
    }

bool setup_fishbot();
void loop_fishbot_control();
void loop_fishbot_transport();

bool microros_setup_transport_udp_client_();
bool microros_setup_transport_serial_();

void callback_odom_publisher_timer_(rcl_timer_t *timer, int64_t last_call_time);
void callback_twist_subscription_(const void *msgin);
void callback_config_service_(const void *req, void *res);

#endif // __FISHBOT_H__