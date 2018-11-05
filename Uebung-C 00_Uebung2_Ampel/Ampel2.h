//Ampel2.h

#define true 1
#define false 0

#define traffic_lights = P1

//Side road lights
#define main_road_green P1^1
#define main_road_yellow P1^3
#define main_road_red P1^5

//Main road lights
#define side_road_green P1^4
#define side_road_yellow P1^2
#define side_road_red P1^0

//side road sensors
#define side_road_sensor_1 P1^6
#define side_road_sensor_2 P1^7

void init();
void delay();
void cycle();
