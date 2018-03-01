#ifndef BOARDITERATOR_H
#define BOARDITERATOR_H


class Gomoku;
class Player;
class Rules;

typedef enum PositionAnalyse {
	ITERATION_END = 0, OTHER = 3, MY_STONE = 1, CAN_PUT_STONE =2, ENNEMY_STONE = -1
} PositionAnalyse;

class BoardIterator
{
	protected:
		
		int x;
		int y;
		int ox;
		int oy;
		Gomoku *gomoku;

		PositionAnalyse analyse(Player &player);

	
	public:

		BoardIterator(Gomoku *gomoku);
		~BoardIterator();
		void reset();
		virtual PositionAnalyse operator()(Player &player, bool &newLine) = 0;
		inline int getX() {return x;}
		inline int getY() {return y;}

};

class VerticalIterator : public BoardIterator
{
	private:
	
	public:

		VerticalIterator(Gomoku *gomoku);
		~VerticalIterator();
		virtual PositionAnalyse operator()(Player &player, bool &newLine);

};

class HorizontalIterator : public BoardIterator
{
	private:
	
	public:

		HorizontalIterator(Gomoku *gomoku);
		~HorizontalIterator();
		virtual PositionAnalyse operator()(Player &player, bool &newLine);

};

class DLeftIterator : public BoardIterator
{
	private:
		
	public:

		DLeftIterator(Gomoku *gomoku);
		~DLeftIterator();
		virtual PositionAnalyse operator()(Player &player, bool &newLine);

};

class DRightIterator : public BoardIterator
{
	private:
	
	public:

		DRightIterator(Gomoku *gomoku);
		~DRightIterator();
		virtual PositionAnalyse operator()(Player &player, bool &newLine);

};


#endif

