#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>

class Vector2D {

private:

	float x;
	float y;
	const float r = 1.00;
	float a;
	
public:

	Vector2D();
	Vector2D(float a);

	void setAngle(float angle);
	void setXY(float x, float y);

	void inverseX();
	void inverseY();
	void calcAngle();
	void calcXY();

	float X();
	float Y();
	float A();

	Vector2D& Add(const Vector2D vec);
	Vector2D& Substract(const Vector2D vec);
	Vector2D& Multiply(const Vector2D vec);
	Vector2D& Divide(const Vector2D vec);

	friend Vector2D& operator+(Vector2D vec1,const Vector2D vec2);
	friend Vector2D& operator-(Vector2D vec1,const Vector2D vec2);
	friend Vector2D& operator*(Vector2D vec1,const Vector2D vec2);
	friend Vector2D& operator/(Vector2D vec1,const Vector2D vec2);

	Vector2D& operator+=(const Vector2D vec);
	Vector2D& operator-=(const Vector2D vec);
	Vector2D& operator*=(const Vector2D vec);
	Vector2D& operator/=(const Vector2D vec);

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};
