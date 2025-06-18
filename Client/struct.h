#pragma once

struct Vector2
{
	float x;
	float y;

public:
	Vector2& operator= (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

public:
	Vector2()
		: x(0.0f)
		, y(0.0f)
	{}

	Vector2(float _x, float _y) 
		: x(_x)
		, y(_y)
	{}

	Vector2 (int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{ }

	Vector2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}
};