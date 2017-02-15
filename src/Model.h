#ifndef MODEL_H
#define MODEL_H

struct typedef Model {
	Player player;
	lgt_wall p_lw;
	Player pc;
	lgt_wall pc_lw;
}

struct typedef Cycle {
	int x;
	int y;
	int speed;
	int direction[];
}Cycle;

struct typedef lgt_wall {
	/* linked list catalouging lightwalls
	Update the wall pixel by pixel per movement at direction
	change save segment for later render calls*/
	int place_holder;
	
}

struct typedef Player {
	Cycle cycle;
	int life;
	
}Player;
