#pragma once

struct Cell
{
	int isMine;
	bool revealed;
	int flagged;
	int adj;
	bool dangerous;
};