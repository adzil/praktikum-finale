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
#define ball_size 2
#define pad_size 16
#define pad_thick 3
#define pad_offset 2
#define screen_x 64
#define screen_y 48

/* Game configuration dependent constants */
#define pad_ypos screen_y - pad_offset - pad_thick

#endif /* GAME_H_ */
