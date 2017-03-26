#include "Board.h"
#include "Snake.h"
#include "Goal.h"
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

bool Board::IsObstacle(const Location & loc) const
{
	return obstacles[loc.y*width+loc.x];
}

void Board::SpawnObstacles(std::mt19937 rng, const Snake & snake, const Goal & goal)
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
	} while (snake.IsInTile(newLoc) || obstacles[i] || goal.GetLocation() == newLoc);

	obstacles[i] = true;
}

void Board::DrawObstacles()
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if(obstacles[y*width + x]) DrawCell({ x,y }, obstacleColor);
		}
	}
}
