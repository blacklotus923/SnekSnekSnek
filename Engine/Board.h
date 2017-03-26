#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	Board( Graphics& gfx );
	void DrawCell( const Location& loc,Color c );
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard( const Location& loc ) const;
	void DrawBorder();
	int EatAt(const Location& loc);
	void SpawnRock(std::mt19937 rng, const class Snake& snake);
	void SpawnFruit(std::mt19937 rng, const class Snake& snake);
	void SpawnPoison(std::mt19937 rng, const class Snake& snake);
	void DrawBoard();
private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color goalColor = Colors::Red;
	static constexpr Color poisonColor = { 31,4,31 };
	static constexpr int dimension = 20;
	static constexpr int cellPadding = 1;
	static constexpr int width = 32;
	static constexpr int height = 24;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int x = 70;
	static constexpr int y = 50;
	static constexpr int poisonPercent = 40;
	int board[width * height] = { 0 }; //0=empty, 1=fruit, 2=rock, 3=poison
	Graphics& gfx;
};