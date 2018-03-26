#ifndef MINMAXDYNAMICPLAYER_H
#define MINMAXDYNAMICPLAYER_H

#include "player.h"

class Choice
{
	public:
		unsigned char x;
		unsigned char y;
		HeuristicBoard myHeuristic;
		HeuristicBoard ennemyHeuristic;
		std::vector<std::pair<unsigned char, unsigned char>> captured;
	
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

		long long heuristic(HeuristicBoard &heuristic, HeuristicBoard &ennemyHeuristic, int depth, bool ennemy = false);
		long long min(int depth, long long minBestOption, long long maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH);
		long long max(int depth, long long minBestOption, long long maxBestOption, Rules &rules, HeuristicBoard myH, HeuristicBoard ennemyH);
		void startMinMax(int &rx, int &ry, Rules &rules);
		bool win(int &rx, int &ry, Rules &rules);
		std::multimap<long long, Choice> heuristicMap(Rules &rules, Player *player, int depht, HeuristicBoard &myOrigin, HeuristicBoard &ennemyOrigin, bool focus = false);


	public:

		MinMaxDynamicPlayer(int d);
		~MinMaxDynamicPlayer();
		virtual void play(Rules &rules, Interface &interfacce);
};

#endif
