#pragma once
#include <math.h>
#include "../Utils/Property.h"

using namespace::std;

class Vector
{
public:
	Vector();
	Vector(float x, float y, float z = 0.0f);

#pragma region Operators
    void operator=(const Vector& vec);
    Vector operator+(const Vector& other);
    Vector operator-(const Vector& other);
    Vector operator*(float n);
    Vector operator/(float n);
#pragma endregion

#pragma region properties
    PROPERTY(float, x);
    GET(x) { return this->_vector[0]; }
    SET(x) { this->_vector[0] = value; }

    PROPERTY(float, y);
    GET(y) { return this->_vector[1]; }
    SET(y) { this->_vector[1] = value; }

    PROPERTY(float, z);
    GET(z) { return this->_vector[2]; }
    SET(z) { this->_vector[2] = value; }

    PROPERTY(float, length);
    GET(length) { return this->getLength(); }
#pragma endregion

private:
    float _vector[4];
    float getLength();
};

