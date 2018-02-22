#ifndef MINMAXDYNAMICPLAYER_H
#define MINMAXDYNAMICPLAYER_H

#include "player.h"
#include "heuristicBoard.h"

class Choice
{
	public:
		unsigned char x;
		unsigned char y;
		HeuristicBoard myHeuristic;
		HeuristicBoard ennemyHeuristic;
	
		Choice(unsigned char x, unsigned char y, HeuristicBoard *myHeuristic, HeuristicBoard *ennemyHeuristic, bool ennemy = false);
		Choice();
		~Choice();
};

class MinMaxDynamicPlayer : public Player
{
	static const unsigned char depthWidths[10];

	private:

		unsigned long complexity;
		int minMaxDepth;
		HeuristicBoard myHeuristic;
		HeuristicBoard ennemyHeuristic;

		inline virtual void setGomoku(Gomoku *gomoku) {this->gomoku = gomoku; myHeuristic.gomoku = gomoku; ennemyHeuristic.gomoku = gomoku;}
		inline virtual void setColor(Stone color) {this->stoneColor = color; myHeuristic.stone =color; ennemyHeuristic.stone = (color == WHITE ? BLACK : WHITE);}
		int heuristic(HeuristicBoard &heuristic, HeuristicBoard &ennemyHeuristic);
		int min(int depth, int minBestOption, int maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH);
		int max(int depth, int minBestOption, int maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH);
		void startMinMax(int &rx, int &ry, Rules &rules);
		bool win(int &rx, int &ry, Rules &rules);
		std::map<int, Choice> heuristicMap(Rules &rules, Player *player, bool focus = false);


	public:

		virtual void observe(Rules &rules, int x, int y);
		MinMaxDynamicPlayer(int d);
		~MinMaxDynamicPlayer();
		virtual void play(Rules &rules, int &x, int &y);
};

#endif
