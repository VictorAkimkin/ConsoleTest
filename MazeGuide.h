#pragma once
#include <algorithm>
#include <set>
#include <map>
#define _i 1
#define _WALL -1

unsigned char test_maze[][15] = {
	//0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},// 0
	{_i,_i,_i,_i,_i,_i, 0,_i,_i,_i,_i,_i,_i, 0, 0},// 1
	{_i, 0, 0, 0, 0,_i, 0, 0, 0, 0, 0, 0, 0,_i, 0},// 2
	{_i, 0,_i,_i,_i,_i,_i,_i,_i,_i, 0, 0, 0,_i, 0},// 3
	{_i, 0,_i,_i, 0, 0, 0, 0, 0,_i, 0, 0, 0,_i, 0},// 4
	{ 0, 0, 0, 0, 0,_i,_i,_i, 0,_i, 0, 0, 0, 0, 0},// 5
	{ 0, 0, 0, 0, 0, 0, 0,_i, 0,_i,_i,_i,_i, 0,_i},// 6
	{ 0, 0,_i,_i,_i,_i, 0,_i, 0, 0, 0, 0, 0, 0,_i},// 7
	{ 0, 0,_i,_i,_i,_i, 0,_i, 0, 0, 0, 0, 0,_i,_i},// 8
	{ 0, 0,_i, 0, 0,_i, 0,_i,_i,_i,_i,_i,_i, 0, 0},// 9
	{ 0, 0,_i, 0, 0, 0, 0, 0, 0, 0, 0,_i, 0, 0, 0},//10
	{ 0, 0,_i, 0, 0,_i, 0,_i, 0, 0, 0, 0, 0, 0, 0},//11
	{ 0, 0,_i,_i,_i,_i, 0,_i, 0, 0, 0, 0,_i,_i, 0},//12
	{ 0, 0, 0, 0, 0, 0, 0,_i,_i,_i,_i,_i,_i, 0, 0},//13
	{ 0,_i,_i,_i,_i,_i, 0, 0, 0, 0, 0, 0,_i,_i, 0},//14
	{ 0, 0,_i,_i, 0,_i,_i,_i,_i,_i,_i,_i, 0,_i, 0},//15
	{ 0, 0,_i,_i, 0,_i, 0, 0, 0, 0, 0, 0, 0, 0, 0},//16
};

class MazeGuide
{
public:
	template <int ROW, int COL>
	MazeGuide(unsigned char const (&_mass)[ROW][COL], std::pair<int, int> _entrance, std::pair<int, int> _exit);
	~MazeGuide();
	// types
private:
	
	struct MATRIX
	{
		MATRIX(std::pair<int, int>& other) : row(other.first), col(other.second) {}
		MATRIX(int _row, int _col) : row(_row), col(_col) {}
		int row, col;
		const bool operator ==(const MATRIX& other) { return (this->col == other.col && this->row == other.row); };
		const bool operator !=(const MATRIX& other) { return !(*this == other); };
		operator std::pair<int, int>()
		{
			return { row,col };
		};
	};
#define _NotFound MATRIX {-1,-1}
	
	enum DIRECTION { _center = 0, _left = 1, _right = 2, _up = 3, _down = 4 };
	
	// methods
public:
	std::vector<std::pair<int, int>> FindExit();
	void ShowMaze();
private:
	void MarkAraund(MATRIX m);
	bool IsZeroPoint(MATRIX m, DIRECTION dir);
	int pointValue(MATRIX m);
	void MarkPoint(MATRIX m, DIRECTION dir);
	std::vector<std::pair<int, int>> GetPath();
	MATRIX MinDirection(MATRIX point);
	
	// variables
private:
	std::vector<std::pair<int, int>> path;
	MATRIX MazeEntrance, MazeExit;
	std::set<std::pair<int, int>> lastPoints;
	int pathlenght{};
	int** maze{}, maxrow, maxcol;

};

template <int ROW, int COL>
MazeGuide::MazeGuide(unsigned char const (&_mass)[ROW][COL], std::pair<int, int> _entrance, std::pair<int, int> _exit)
	:MazeEntrance(_entrance), MazeExit(_exit), maze(new int* [ROW]), maxrow(ROW), maxcol(COL)
{
	for (int r{}; r < maxrow; ++r)
		maze[r] = new int[maxcol];
	for (int r{}; r < maxrow; ++r)
		for (int c{}; c < maxcol; ++c)
			_mass[r][c] ? maze[r][c] = _WALL : maze[r][c] = 0;
}
MazeGuide::~MazeGuide()
{
	if (!maze) return;
		for (int r{}; r < maxrow; ++r)
		  delete[] maze[r];
		delete[] maze;
}
// Поиск
std::vector<std::pair<int, int>> MazeGuide::FindExit()
{
	if (MazeEntrance == MazeExit) return{};
	lastPoints.insert({ MazeEntrance.row, MazeEntrance.col });

	maze[MazeEntrance.row][MazeEntrance.col] = 1; ++pathlenght;
	while (!lastPoints.empty())
	{
		std::set<std::pair<int, int>> pointsForProcessing;
		pointsForProcessing.swap(lastPoints);
		++pathlenght;		
		while (!pointsForProcessing.empty())
		{
			MATRIX point((*pointsForProcessing.begin()).first, (*pointsForProcessing.begin()).second);
			MarkAraund(point);
			pointsForProcessing.erase(pointsForProcessing.begin());
			if (point == MazeExit)
			{
				lastPoints.clear();
				pointsForProcessing.clear();
			}
		}
	}
	return  GetPath();
}
//------------------------------------------------------------------------------
void MazeGuide::MarkAraund(MATRIX point)
{
	if (IsZeroPoint(point, _left))
	{
		MarkPoint(point, _left); lastPoints.insert({ point.row, point.col - 1 });
	}
	if (IsZeroPoint(point, _right))
	{
		MarkPoint(point, _right); lastPoints.insert({ point.row, point.col + 1 });
	}
	if (IsZeroPoint(point, _up))
	{
		MarkPoint(point, _up); lastPoints.insert({ point.row - 1,point.col });
	}
	if (IsZeroPoint(point, _down))
	{
		MarkPoint(point, _down); lastPoints.insert({ point.row + 1, point.col });
	}
}

bool MazeGuide::IsZeroPoint(MATRIX point, DIRECTION dir)
{
	switch (dir) {
	case _left:	if (point.col > 0)		return !maze[point.row][point.col - 1]; break;
	case _right:if (point.col < (maxcol-1)) return !maze[point.row][point.col + 1]; break;
	case _up:	if (point.row > 0)		return !maze[point.row - 1][point.col]; break;
	case _down:	if (point.row < (maxrow-1)) return !maze[point.row + 1][point.col]; break;
	}
	return false;
}
int MazeGuide::pointValue(MATRIX point)
{
	return maze[point.row][point.col];
}
void MazeGuide::MarkPoint(MATRIX m, DIRECTION dir)
{
	switch (dir) {
	case _left:	maze[m.row][m.col-1] = pathlenght; break;
	case _right:maze[m.row][m.col+1] = pathlenght; break;
	case _up:	maze[m.row-1][m.col] = pathlenght; break;
	case _down:	maze[m.row+1][m.col] = pathlenght; break;
	}
}
std::vector<std::pair<int, int>> MazeGuide::GetPath()
{
	if (path.size())return path;
	std::vector<std::pair<int, int>> revered_path;
	MATRIX point(MazeExit);
	while (point != MazeEntrance && point != _NotFound)
	{
		revered_path.push_back(point);
		point = MinDirection(point);
	}
	if (point == _NotFound) return {};
	revered_path.push_back(point);
	path = std::vector<std::pair<int, int>>(revered_path.rbegin(), revered_path.rend());
	return path;
}
MazeGuide::MATRIX MazeGuide::MinDirection(MATRIX point)
{
	std::map <int, MATRIX> _set;
	MATRIX left_point = { point.row, point.col - 1 };
	MATRIX right_point = { point.row, point.col + 1 };
	MATRIX up_point = { point.row - 1, point.col };
	MATRIX down_point = { point.row + 1, point.col };
	if (point.col > 0)	
		_set.insert({ pointValue(left_point),left_point });
	if (point.col < (maxcol-1))
		_set.insert({pointValue(right_point), right_point });
	if (point.row > 0)		
		_set.insert({ pointValue(up_point),up_point });
	if (point.row < (maxrow-1))
		_set.insert({ pointValue(down_point),down_point });
	_set.erase(-1);
	if (!_set.empty()) 
		return (*_set.begin()).second;
	return _NotFound;
}
void MazeGuide::ShowMaze()
{
	for (int r{}; r < maxrow; ++r)
	{
		cout << "\n";
		for (int c{}; c < maxcol; ++c)
		{
			(maze[r][c] < 10 && maze[r][c] != -1) ? cout << "  " : cout << " ";
			cout << maze[r][c];

		}
	}
	cout << "\n";
}
