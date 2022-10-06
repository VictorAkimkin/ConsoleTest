#pragma once
#define _i 1
unsigned char test_mass[][20] = {
	{ 0, 0, _i, _i,  0,  0,  0, 0,  0, 0,  0,  0,  0,  0, 0},
	{_i,_i, _i, _i, _i, _i,  0, 0,  0, 0,  0,  0,  0,  0, 0},
	{_i, 0,	 0,	 0, 0,  _i,  0, 0,  0, 0,  0,  0,  0,  0, 0},
	{_i, 0, _i, _i, _i, _i,  0, 0,  0, 0,  0,  0,  0, _i, 0},
	{_i, 0, _i, _i,  0,  0,  0, 0,  0, 0,  0,  0,  0, _i, 0},
	{ 0, 0,	 0,	 0,  0,  0,  0, 0,  0, 0,  0,  0,  0,  0, 0},
	{ 0, 0,	 0,	 0,  0,  0,  0, 0,  0, 0,  0, _i,  0,  0, 0},
	{ 0, 0, _i, _i, _i, _i,  0, 0,  0, 0,  0,  0,  0,  0, 0},
	{ 0, 0, _i, _i, _i, _i,  0, 0,  0, 0,  0,  0,  0,  0, 0},
	{ 0, 0, _i,	 0,  0, _i,  0, 0,  0, 0,  _i,_i,  0,  0, 0},
	{ 0, 0, _i,	 0,  0, _i,  0, 0,  0, 0,  0, _i,  0,  0, 0},
	{ 0, 0, _i,	 0,  0, _i,  0, 0,  0, 0,  0,  0,  0,  0, 0},
	{ 0, 0, _i, _i, _i, _i,  0, 0,  0, 0,  0,  0, _i, _i, 0},
	{ 0, 0,  0,  0,  0,  0,  0, 0,  0, 0,  0, _i, _i,  0, 0},
	{ 0, 0, _i, _i, _i, _i,  0, 0,  0, 0,  0,  0, _i, _i, 0},
	{ 0, 0, _i, _i,  0, _i, _i, 0,  0, 0,  0,  0,  0, _i, 0},
	{ 0, 0, _i, _i,  0, _i,  0, 0,  0, 0,  0,  0,  0,  0, 0},
};

class Isle
{
public:

	Isle() = delete;
	Isle(Isle&) = delete;
	Isle(Isle&&) = delete;
	template <int ROW, int COL>
	Isle(unsigned char const (&mass)[ROW][COL]);
	Isle(unsigned char** mass, int _size_row, int _size_col);
	template <int ROW, int COL>
	Isle(unsigned char (*mass)[ROW][COL]);
	template <int COL>
	Isle(unsigned char(*mass)[COL], int _size_row);
	~Isle();
	// types
private:
	struct MATRIX
	{
		int row,col;
		const bool operator ==(const MATRIX& other) { return (this->col == other.col && this->row == other.row); };
		const bool operator !=(const MATRIX& other) { return !(*this == other); };
	};
#define _MATRIX_ERROR (MATRIX)(-1,-1)
#define _MARKED_ISLE  (unsigned char)( - 1)
#define _NOT_ISLE 0
	// methods
public:
	int GetIslandsNum();

private:
	MATRIX FindIslandFirstPoint(Isle::MATRIX start_point);
	bool IsIsle(Isle::MATRIX point);
	void MarkIsle(MATRIX start_point);


	// variables
private:
	unsigned char** mass{};
	int size_col{}, size_row{};
	int i_quantity{};
};

template <int ROW, int COL>
Isle::Isle(unsigned char const (&mass)[ROW][COL]) :mass(new unsigned char* [ROW]),
size_col(COL), size_row(ROW)
{
	for (int r = 0; r < size_row; ++r)
		this->mass[r] = new unsigned char[size_col];
	for (int r{}; r < size_row; ++r)
		for (int c{}; c < size_col; ++c)
			this->mass[r][c] = mass[r][c];
}
Isle::Isle(unsigned char** mass, int _size_row, int _size_col) :mass(new unsigned char* [_size_row]),
size_col(_size_col), size_row(_size_row)
{
	for (int r = 0; r < size_row; ++r)
		this->mass[r] = new unsigned char[size_col];
	for (int r{}; r < size_row; ++r)
		for (int c{}; c < size_col; ++c)
			this->mass[r][c] = mass[r][c];
}
template <int ROW, int COL>
Isle::Isle(unsigned char (*mass)[ROW][COL]) :mass(new unsigned char* [ROW]),
size_col(COL), size_row(ROW)
{
	for (int r = 0; r < size_row; ++r)
		this->mass[r] = new unsigned char[size_col];
	for (int r{}; r < size_row; ++r)
		for (int c{}; c < size_col; ++c)
			this->mass[r][c] = (*mass)[r][c];
}
template <int COL>
Isle::Isle(unsigned char (*mass)[COL],int _size_row) :mass(new unsigned char* [_size_row]),
size_col(COL), size_row(_size_row)
{
	for (int r = 0; r < size_row; ++r)
		this->mass[r] = new unsigned char[size_col];
	for (int r{}; r < size_row; ++r)
		for (int c{}; c < size_col; ++c)
			this->mass[r][c] = mass[r][c];
}



Isle::~Isle()
{
	if (!mass) return;
	for (int r = 0; r < size_row; ++r)
		delete[] mass[r];
	delete[] mass;
}
int Isle::GetIslandsNum()
{
	MATRIX cur_point{};
	i_quantity = 0;
	for (int r{}; r < size_row; ++r)
		for (int c{}; c < size_col; ++c)
		{
			if ((cur_point = FindIslandFirstPoint({ r,c })) != _MATRIX_ERROR)
			{
				c = cur_point.col;
				r = cur_point.row;
				++i_quantity;
				MarkIsle(cur_point);
			}
		}
	return i_quantity;
}
bool Isle::IsIsle(Isle::MATRIX point)
{
	if (point.row < 0 || point.col < 0 || point.row >= size_row || point.col >= size_col) return false;
	return (mass[point.row][point.col] != _NOT_ISLE && mass[point.row][point.col] != _MARKED_ISLE);
}
Isle::MATRIX Isle::FindIslandFirstPoint(Isle::MATRIX start_point)
{
	int c{};
	for (int r = start_point.row; r < size_row; ++r)
	{
		r == start_point.row ? c = start_point.col : c = 0;
		for (c; c < size_col; ++c)
			if (IsIsle({ r,c }))
				return { r,c };
	}
	return _MATRIX_ERROR;
}
void Isle::MarkIsle(MATRIX point)
{
	mass[point.row][point.col] = _MARKED_ISLE;
	if (IsIsle({ point.row - 1, point.col }))	MarkIsle({ point.row - 1, point.col });
	if (IsIsle({ point.row + 1, point.col }))	MarkIsle({ point.row + 1, point.col });
	if (IsIsle({ point.row, point.col - 1 }))	MarkIsle({ point.row, point.col - 1 });
	if (IsIsle({ point.row, point.col + 1 }))	MarkIsle({ point.row, point.col + 1 });
}
