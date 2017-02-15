#ifndef MODEL_H
#define MODEL_H

struct typedef Cycle {
	int x;
	int y;
	int speed;
	int direction[];
}Cycle;

struct typedef Player {
	Cycle cycle;
	int life;
	
}Player;
