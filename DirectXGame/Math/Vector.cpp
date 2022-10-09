#include "Vector.h"

Vector::Vector()
{
	for (int i = 0; i < 4; i++)
	{
		this->_vector[i] = 0;
	}
}

Vector::Vector(float x, float y, float z)
{
	this->_vector[0] = x;
	this->_vector[1] = y;
	this->_vector[2] = z;
	this->_vector[3] = 0;
}

float Vector::getLength()
{
	float x2 = this->_vector[0] * this->_vector[0];
	float y2 = this->_vector[1] * this->_vector[1];
	float z2 = this->_vector[2] * this->_vector[2];

	return sqrtf(x2 + y2 + z2);
}

void Vector::operator=(const Vector& vec)
{
	this->_vector[0] = vec._vector[0];
	this->_vector[1] = vec._vector[1];
	this->_vector[2] = vec._vector[2];
	this->_vector[3] = vec._vector[3];
}

Vector Vector::operator+(const Vector& vec)
{
	Vector temp = Vector();
	temp._vector[0] = this->_vector[0] + vec._vector[0];
	temp._vector[1] = this->_vector[1] + vec._vector[1];
	temp._vector[2] = this->_vector[2] + vec._vector[2];
	temp._vector[3] = this->_vector[3] + vec._vector[3];

	return temp;
}

Vector Vector::operator-(const Vector& vec)
{
	Vector temp = Vector();
	temp._vector[0] = this->_vector[0] - vec._vector[0];
	temp._vector[1] = this->_vector[1] - vec._vector[1];
	temp._vector[2] = this->_vector[2] - vec._vector[2];
	temp._vector[3] = this->_vector[3] - vec._vector[3];

	return temp;
}

Vector Vector::operator*(float n)
{
	Vector temp = Vector();
	temp._vector[0] = this->_vector[0] * n;
	temp._vector[1] = this->_vector[1] * n;
	temp._vector[2] = this->_vector[2] * n;
	temp._vector[3] = this->_vector[3] * n;

	return temp;
}

Vector Vector::operator/(float n)
{
	Vector temp = Vector();
	temp._vector[0] = this->_vector[0] / n;
	temp._vector[1] = this->_vector[1] / n;
	temp._vector[2] = this->_vector[2] / n;
	temp._vector[3] = this->_vector[3] / n;

	return temp;
}
