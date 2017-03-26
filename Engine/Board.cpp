#include "Board.h"
#include "Snake.h"
#include <assert.h>

Board::Board( Graphics& gfx )
	:
	gfx( gfx )
{}

void Board::DrawCell( const Location & loc,Color c )
{
	assert( loc.x >= 0 );
	assert( loc.x < width );
	assert( loc.y >= 0 );
	assert( loc.y < height );

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim( loc.x * dimension + off_x + cellPadding,loc.y * dimension + off_y + cellPadding,dimension - cellPadding * 2,dimension - cellPadding * 2,c );
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard( const Location & loc ) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	// top
	gfx.DrawRect( left,top,right,top + borderWidth,borderColor );
	// left
	gfx.DrawRect( left,top + borderWidth,left + borderWidth,bottom - borderWidth,borderColor );
	// right
	gfx.DrawRect( right - borderWidth,top + borderWidth,right,bottom - borderWidth,borderColor );
	// bottom
	gfx.DrawRect( left,bottom - borderWidth,right,bottom,borderColor );
}

int Board::EatAt(const Location & loc)
{
	const int i = loc.y * width + loc.x;
	const int r = board[i];
	if (r == 1 || r ==3) board[i] = 0;
	return r;
}

void Board::SpawnRock(std::mt19937 rng, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	int i;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
		i = newLoc.y * width + newLoc.x;
	} while (snake.IsInTile(newLoc) || board[i] == 1 || board[i] == 2);

	board[i] = 2;
}

void Board::SpawnFruit(std::mt19937 rng, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	Location newLoc;
	int i;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
		i = newLoc.y * width + newLoc.x;
	} while (snake.IsInTile(newLoc) || board[i] == 1 || board[i] == 2);

	board[i] = 1;
}

void Board::SpawnPoison(std::mt19937 rng, const Snake & snake)
{
	std::uniform_int_distribution<int> poisonDist(0, 100);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			const int i = y*width + x;
			if (poisonDist(rng) < poisonPercent && !snake.IsInTile({ x,y }) && board[i]!=1) board[i] = 3;
			else board[i] = 0;
		}
	}
}

void Board::DrawBoard()
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			const int cell = board[y*width + x];
			if (cell == 1) DrawCell({ x,y }, goalColor);
			else if (cell == 2) DrawCell({ x,y }, obstacleColor);
			else if (cell == 3) DrawCell({ x,y }, poisonColor);
		}
	}
}
