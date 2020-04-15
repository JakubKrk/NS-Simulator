#pragma once


struct Point
{
	float x;
	float y;

	Point() {}
	Point(float mx, float my)
	{
		this->x = mx;
		this->y = my;
	}
	~Point() {}

};