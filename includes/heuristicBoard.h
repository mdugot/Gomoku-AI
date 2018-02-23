#ifndef HEURISTICBOARD_H
#define HEURISTICBOARD_H

#include "gomoku.h"

#define GET_HH(x)  ((x & 0xF000) >> 12)
#define GET_VH(x)  ((x & 0x0F00) >> 8)
#define GET_DLH(x) ((x & 0x00F0) >> 4)
#define GET_DRH(x) (x & 0x000F)

#define SET_HH(x,y)  ((x & 0x0FFF) | (y << 12))
#define SET_VH(x,y)  ((x & 0xF0FF) | (y << 8))
#define SET_DLH(x,y) ((x & 0xFF0F) | (y << 4))
#define SET_DRH(x,y) ((x & 0xFFF0) | (y))

#define REMOVE_THREAT(x) score -= levels[((x) > 5 ? 5 : (x))]
#define ADD_THREAT(x) score += levels[((x) > 5 ? 5 : (x))]

#define WATCH(x,name) if (x < 0 || x >= GW) DEBUG << RED << "WARNING " << name << " : out of limit -> " << x << "\n" << DEFAULT_COLOR

#define L0 0
#define L1 1
#define L2 (long long)(18*18)
#define L3 (long long)L2*L2
#define L4 (long long)L3*L2
#define HAS_WON (long long)L4*L2
#define WIN_STATE (long long)L4*2
#define BIG (long long)HAS_WON*L2

class HeuristicBoard
{
	friend class MinMaxDynamicPlayer;
	friend class HeuristicBoard;
	static const long long levels[6];

	private:

		short int heuristic[GW][GH];
		Gomoku* gomoku;
		char stone;

		void getAdjacent(char x, char y, char vx, char vy, unsigned char &before, unsigned char &after, unsigned char &beforeWall, unsigned char &afterWall);
		int getBestLevel(unsigned char x, unsigned char y);
	
	public:
		long long score;

		HeuristicBoard();
		HeuristicBoard(HeuristicBoard *copyFrom);
		~HeuristicBoard();
		HeuristicBoard &put(unsigned char x, unsigned char y, bool prediction = true);
		HeuristicBoard &clear(unsigned char x, unsigned char y);
		void print(int lastX = -1, int lastY = -1);

};

#endif
