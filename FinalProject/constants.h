#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WIDTH = 1200;
const int HEIGHT = 800;
const int BUTTON_HEIGHT = 88; 
const int BUTTON_WIDTH = 309; 
const int LEFT_MENU_X = WIDTH / 5; 
const int LEFT_MENU_Y = 15; 
const int RIGHT_MENU_X = WIDTH / 2; 
const int RIGHT_MENU_Y = 15; 
const int UNDER_MENU = HEIGHT - LEFT_MENU_Y - BUTTON_HEIGHT; 
const int ROW_HEIGHT = 20; 
const int NUM_VISIBLE_ROWS = UNDER_MENU / ROW_HEIGHT; 

#endif // CONSTANTS_H