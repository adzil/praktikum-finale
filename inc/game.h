/**
 * Praktikum Finale: The Pong-Pong project
 * Final project for embedded system design experiment course.
 *
 * Created by:
 * * Fadhli Dzil Ikram (13212035)
 * * Febby Purnama M. (13212041)
 *
 */

#ifndef GAME_H_
#define GAME_H_

/* Game global configuration */
#define ball_size 4
#define ball_speed 2
#define pad_size 20
#define pad_thick 4
#define pad_offset 3
#define screen_x 96
#define screen_y 64
#define accel_thresh_slow 10
#define accel_thresh_fast 20
#define speed_slow 1
#define speed_fast 2

#define score_buffer 5
#define score_xpos 5
#define score_ypos 5
#define char_width 6
#define char_height 7

/* Game configuration dependent constants */
#define pad_ypos screen_y - pad_offset - pad_thick

#endif /* GAME_H_ */
