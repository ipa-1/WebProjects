#include <math.h>
#include "mathLib2D.h"
#include<tuple>

typedef tuple <int,int,int> color;

// Particle Class

/**
*  \brief Particle Default constructor
*  \return Particle
*/
Particle::Particle(){
	this->location= Point2D(4.0,2.0);
	this->mC= colour(0,0,0);
	this->size= 0;
	this->direction= Vec2D(1,1);
	this->range=0.0;
	this->speed=0.0;
}

/**
 *  \brief Particle Constructor with two arguments
 *  \param Point2D inPd location of the point
 	\param colour (R,G,B) random initial colour
 	\param size, an int between 1 and 5 indicating size
 	\param direction, a 2D vector, initially [0,0], stationary
	\param range, an int or float, used in Left-Mouse/Right-Mouse
	\param speed, a float, speed in which particles move
 *  \return Particle
 */
Particle::Particle(Point2D inPd, colour inC, int inS, Vec2D inV, float inR, float inSpeed){
	this->location=inPd;
	this->mC=inC;
	this->size=inS;
	this->direction=inV;
	this->range=inR;
	this->speed=inSpeed;
}

// Point2D Class

/**
*  \brief Point2D Default constructor
*  \return Point2D
*/
Point2D::Point2D(){
	this->mX=0;
	this->mY=0;
}

/**
 *  \brief Point2D Constructor with two arguments
 *  \param inX x value of Point2D
 *  \param inY y value of Point2D
 *  \return Poing2D
 */
Point2D::Point2D(float inX, float inY){
	this->mX=inX;
	this->mY=inY;
}

// Point2D distance to function

/**
 *  \brief Point2D Distance function for vector
 *  \param other , the target Point2D to find the distance to
 *  \return float measurement of the distance
 */
float Point2D::distanceTo(Point2D other){
	return sqrt(pow((other.mX - this->mX),2)+ pow((other.mY-this->mY),2));
}

// Point2D distance to function that does not use square root
/**
 *  \brief Point2D Distance function for vector without square root
 *  \param other , the target Point2D to find the distance to
 *  \return float measurement of the distance
 */
float Point2D::fastDistanceTo(Point2D other){
	return pow((other.mX - this->mX),2)+ pow((other.mY-this->mY),2);
}


// Vec2D Class
/**
 *  \brief Vec2D default class constructor
 *  \return Vec2D
 */
Vec2D::Vec2D(){
	this->mX=0;
	this->mY=0;
}

/**
 *  \brief vec2D class constructor with two arguments
 *  \param inX x value of vector
 *  \param inY y value of vector
 *  \return Vec2D with corresponding x and y value
 */
Vec2D::Vec2D(float inX, float inY){
	this->mX=inX;
	this->mY=inY;
}

/**
 *  \brief vec2D calculates length of vector
 *  \return float measurement of the distance
 */
float Vec2D::length(){
	return sqrt(pow(this->mX,2) + pow(this->mY,2));
}

/**
 *  \brief vec2D Calculates a normalized vector of the given vector
 *  \return vec2D of the normalized vector
 */
Vec2D Vec2D::normalize(){
	//float magnitude = sqrt(pow(this->mX,2) + pow(this->mY,2));
	float m1 = this->length();
	return Vec2D(this->mX/m1, this->mY/m1);
}

/**
 *  \brief vec2D multiplies the given vector by scalar given
 *  \param scalar to multiply the vector by
 *  \return new Vec2D that is multiplied by the scalar
 */
Vec2D Vec2D::multiply(float scalar){
	return Vec2D(this->mX*scalar, this->mY*scalar);
}

/**
 *  \brief Vec2D Creates a vector with two points
 *  \param p1 first point
 *  \param p2 second point
 *  \return Vec2D made of the two points
 */
Vec2D Vec2D::createVector(Point2D p1, Point2D p2){
	return Vec2D(p2.mX - p1.mX,p2.mY-p1.mY);
}

/**
 *  \brief Vec2D Moves a Point2D by a vector
 *  \param source Point2D to move
 *  \return Point2D reflecting the moved Point2D
 */
Point2D Vec2D::movePoint(Point2D source){
	Point2D pointT=Point2D(source.mX+this->mX,source.mY+this->mY);
	return pointT;
}