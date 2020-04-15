#include "Vector2D.h"


Vector2D::Vector2D()
{
	this->a = 0.00;
	calcXY();
}

Vector2D::Vector2D(float a)
{
	this->a = a;
	calcXY();
}

void Vector2D::setAngle(float angle)
{
	if (angle > 360)
	{
		angle = fmod(angle, 360);
	}
	this->a = angle;
	calcXY();
}


void Vector2D::setXY(float x, float y)
{
	float deg = atan2(y, x)* (180 / M_PI);


	deg = fmod(deg, 360);
	setAngle(deg);

}

void Vector2D::calcXY()
{
	this->x = this->r * cos(this->a / (180.0 / M_PI));
	this->y = this->r * sin(this->a / (180.0 / M_PI));

}

void Vector2D::calcAngle()
{
	float deg = atan2(this->y, this->x) * (180 / M_PI);

	if (deg < 0)
	{
		this->a = 360 + deg;
	}
	if (deg >= 0)
	{
		this->a = deg;
	}

}


void Vector2D::inverseX()
{
	this->x = -(this->x);
	calcAngle();
}

void Vector2D::inverseY()
{
	this->y = -(this->y);
	calcAngle();
}

float Vector2D::X()
{
	return this->x;
}

float Vector2D::Y()
{
	return this->y;
}
float Vector2D::A()
{
	return this->a;
}

Vector2D& Vector2D::Add(const Vector2D vec)
{
	 this->x += vec.x;
	 this->y += vec.y;
	 return *this;
}

Vector2D& Vector2D::Substract(const Vector2D vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vector2D& operator+(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Add(vec2);
}

Vector2D& operator-(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Substract(vec2);
}

Vector2D& operator*(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Multiply(vec2);
}

Vector2D& operator/(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Divide(vec2);
}

Vector2D& Vector2D::operator+=(const Vector2D vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D vec)
{
	return this->Substract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D vec)
{
	return this->Divide(vec);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;

}