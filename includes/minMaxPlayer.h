#ifndef MINMAXPLAYER_H
#define MINMAXPLAYER_H

#include "player.h"

class MinMaxPlayer : public Player
{
	private:

		int minMaxDepth;

		virtual int heuristic() = 0;
		int min(int depth, int minBestOption, int maxBestOption, Rules &rules);
		int max(int depth, int minBestOption, int maxBestOption, Rules &rules);
		void startMinMax(int &rx, int &ry, Rules &rules);


	public:

		MinMaxPlayer(int d);
		~MinMaxPlayer();
		virtual void play(Rules &rules, int &x, int &y);
};

class AI1 : public MinMaxPlayer
{
	private:

		virtual int heuristic();

	public:

		AI1(int d);
		~AI1();
};


#endif

