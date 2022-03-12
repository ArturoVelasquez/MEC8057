#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/camera.h>
#include <webots/touch_sensor.h>
#include <webots/gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIME_STEP 64
#define ENCODER_UNIT 0.25

enum BLOB_TYPE { RED, GREEN, BLUE, NONE };

int main(int argc, char **argv) {


  int width, height;
  int i, j;
  int red, blue, green;
  const char *color_names[3] = {"red", "green", "blue"};
  enum BLOB_TYPE current_blob;



  //bool avoid_obstacle_counter = 0;
  double left_encoder_offset = 0.0;
  double right_encoder_offset = 0.0;
  double left_encoder_offset_return = 0.0;
  double right_encoder_offset_return = 0.0;
  double force_value =0.0;
  
  double old_lat=0.0;
  double old_lon=0.0;

  float left_speed=0.0;
  float right_speed=0.0;

  // Turns needed for the diferentia robot to make a 0.5m radius circle
  float circle_goal[2] = {19.687314, 32.672564} ;
  // Turns needed for the diferentia robot to make advance 1 m and rotate 90 degres.
  float line_goal = 8.0;
  float rotate_goal =1.57079632;
  float encoder_value[4];
  int square=0;
  int search_period=2;
  bool initial_steps[2] ={0};
  bool right_obstacle=0;
  bool left_obstacle=0;
  bool found=0;
  bool turn=0;
  bool load=0;
  /*
  * device_name[0] -> distance sensor right
  * device_name[1] -> distance sensor left
  * device_name[2] -> encoder right
  * device_name[3] -> encoder left
  * device_name[4] -> motor right
  * device_name[5] -> motor left
  * device_name[6] -> camera
  * device_name[7] -> force sensor
  * device_name[8] -> GPS
  */
  char divice_names[9][10] = {"l_dista_s", "r_dista_s","l_encod_s","r_encod_s","r_motor_a","l_motor_a", "u_camer_s","u_force_s","u__gps__s"};
  WbDeviceTag device[9];
  wb_robot_init();



  //int i;
  for (i = 0; i < 9; i++) {
    device[i] = wb_robot_get_device(divice_names[i]);
  }
  wb_distance_sensor_enable(device[0], TIME_STEP);
  wb_distance_sensor_enable(device[1], TIME_STEP);

  wb_position_sensor_enable(device[2], TIME_STEP);
  wb_position_sensor_enable(device[3], TIME_STEP);

  wb_camera_enable(device[6], TIME_STEP);
  
  wb_touch_sensor_enable(device[7], TIME_STEP);
  
  wb_gps_enable(device[8], TIME_STEP);

  width = wb_camera_get_width(device[6]);
  height = wb_camera_get_height(device[6]);

  wb_motor_set_position (device[4], INFINITY);
  wb_motor_set_position (device[5], INFINITY);

  wb_motor_set_velocity(device[4], 0.0);
  wb_motor_set_velocity(device[5], 0.0);


  while (wb_robot_step(TIME_STEP) != -1) {
    force_value = wb_touch_sensor_get_value(device[7]);
    /***
    *** Start of INITIALIZATION ROUTINE
    ***/
    if (initial_steps[1] ==0){
      encoder_value[0] = wb_position_sensor_get_value(device[2])-left_encoder_offset;
      encoder_value[1] = wb_position_sensor_get_value(device[3])-right_encoder_offset;
      if (square<4){
        if(initial_steps[0] ==0){
          left_speed = 2;
          right_speed =2;
          if(encoder_value[0] > line_goal || encoder_value[1] > line_goal){
            initial_steps[0] = 1;
            left_encoder_offset = wb_position_sensor_get_value(device[2]);
            right_encoder_offset = wb_position_sensor_get_value(device[3]);
           }
         }
         else{
          left_speed = -2;
          right_speed = 2;
          if(encoder_value[0] > rotate_goal || encoder_value[1] < -rotate_goal){
            initial_steps[0] = 0;
            left_encoder_offset = wb_position_sensor_get_value(device[2]);
            right_encoder_offset = wb_position_sensor_get_value(device[3]);
            square++;
           }
         }
      }
      else if (initial_steps[0] ==0){
        left_speed = 2.48;
        right_speed = 1.52;
        if(encoder_value[0] > circle_goal[0] || encoder_value[1] > circle_goal[1]){
          initial_steps[0] =1;
          left_encoder_offset = wb_position_sensor_get_value(device[2]);
          right_encoder_offset = wb_position_sensor_get_value(device[3]);

        }
      }
      else {
        left_speed = 1.52;
        right_speed = 2.48;
        if(encoder_value[0] > circle_goal[1] || encoder_value[1] > circle_goal[0]){
          initial_steps[1]=1;
          left_speed = 0;
          right_speed = 0;
          left_encoder_offset = wb_position_sensor_get_value(device[2]);
          right_encoder_offset = wb_position_sensor_get_value(device[3]);
        }
      }
    }
    /***
    *** End of INITIALIZATION ROUTINE
    ***/
    
    else if(!found){

      right_obstacle = wb_distance_sensor_get_value(device[0])<350.0;
      left_obstacle = wb_distance_sensor_get_value(device[1])<350.0;
      encoder_value[0] = wb_position_sensor_get_value(device[2])-left_encoder_offset;
      encoder_value[1] = wb_position_sensor_get_value(device[3])-right_encoder_offset;
      
      if( left_speed ==0 ||encoder_value[0]>rotate_goal||encoder_value[1]>rotate_goal){
         left_speed = 2;
         right_speed = 2;
      }
      if (left_obstacle && encoder_value[0]>rotate_goal){
        left_speed = 2;
        right_speed = -2;
        left_encoder_offset = wb_position_sensor_get_value(device[2]);
        right_encoder_offset = wb_position_sensor_get_value(device[3]);
      }
      else if(right_obstacle && encoder_value[0]>rotate_goal) {
        left_speed = -2;
        right_speed = 2;
        left_encoder_offset = wb_position_sensor_get_value(device[2]);
        right_encoder_offset = wb_position_sensor_get_value(device[3]);
        }
      else if (current_blob == GREEN) {
        left_speed =  1;
        right_speed = 1;
        if( green > 1600000){
            left_speed =  0;
            right_speed = 0;
          }
      }
      else if(force_value>0.0 && !right_obstacle && !left_obstacle){
        printf("LOAD READY \n");
        load=1;
           
        encoder_value[2] = wb_position_sensor_get_value(device[2])-left_encoder_offset_return;
        encoder_value[3] = wb_position_sensor_get_value(device[3])-right_encoder_offset_return;
      
        left_speed =  2;
        right_speed = 2;
      
        const double *position = wb_gps_get_values(device[8]);
          
        double lat=position[0];
        double lon=position[1];
         
        if(!turn){  
          if((lat >= old_lat && lat>0) ||(lat <= old_lat && lat<0)){
            left_speed = 2;
            right_speed = -2;
            if(encoder_value[2] > rotate_goal/3 || encoder_value[2] < -rotate_goal/3){
              turn = 1;
              left_encoder_offset_return = wb_position_sensor_get_value(device[2]);
              right_encoder_offset_return = wb_position_sensor_get_value(device[3]);
              old_lat=lat;
              old_lon=lon;
              }
            }
          else if((lon >= old_lon && lon>0) ||(lon <= old_lon && lon<0)){
            left_speed = 2;
            right_speed = -2;
            if(encoder_value[2] > rotate_goal/2 || encoder_value[2] < -rotate_goal/2){
              turn = 1;
              left_encoder_offset_return = wb_position_sensor_get_value(device[2]);
              right_encoder_offset_return = wb_position_sensor_get_value(device[3]);
              old_lat=lat;
              old_lon=lon;
              }
           }
        }
        else if(encoder_value[2] > line_goal/2 || encoder_value[3] > line_goal/2){
            left_encoder_offset_return = wb_position_sensor_get_value(device[2]);
            right_encoder_offset_return = wb_position_sensor_get_value(device[3]);
            old_lat=lat;
            old_lon=lon;
            turn = 0;
          }
        else if(lat<0.1 && lon<0.1 && lat>-0.1 && lon>-0.1){
            left_speed = 0;
            right_speed = 0;
            printf("BACK HOME SAFE \n");
          }
      }
    }
    if (initial_steps[1] ==1 && initial_steps[0]==1 && !load){
      double enlapsed_time = wb_robot_get_time();
      int stopnscout = (int) enlapsed_time;
      if (stopnscout % search_period ==0){
        red=0;
        blue=0;
        green=0;
        const unsigned char *image = wb_camera_get_image(device[6]);
        for (i = width / 3; i < 2 * width / 3; i++) {
          for (j = height / 2; j < 3 * height / 4; j++) {
            red += wb_camera_image_get_red(image, width, i, j);
            blue += wb_camera_image_get_blue(image, width, i, j);
            green += wb_camera_image_get_green(image, width, i, j);
          }
        }
        if ((red >   green) && (red >   blue))
          current_blob = RED;
        else if ((green >  red) && (green >  blue))
          current_blob = GREEN;
        else if ((blue >   red) && (blue >   green))
          current_blob = BLUE;
        else
          current_blob = NONE;
        if (current_blob == NONE) {
          printf("NO COLOR \n");
        }
        else if (current_blob == GREEN) {
          printf("found it GREEN \n");
          search_period=1;
         }
        else {
          printf("COLOR %s \n", color_names[current_blob]);
          
        }
      }
    }
    
    wb_motor_set_velocity(device[4], left_speed);
    wb_motor_set_velocity(device[5], right_speed);
  }
  wb_robot_cleanup();
  return 0;  // EXIT_SUCCESS
}
