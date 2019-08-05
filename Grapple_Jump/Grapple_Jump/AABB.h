//
// C00204076
// Brandon Seah-Dempsey
// Started at 14:32 4 July 2019
// Finished at 
// Time taken: 
// Known bugs: None

#ifndef AABB_H
#define AABB_H

#include "SFML/Graphics.hpp"

#include <iostream>

//
class AABB
{
public:
	AABB(float x, float y, float width, float height);
	~AABB();

	float getX();
	float getY();
	float getWidth();
	float getHeight();

	sf::Vector2f getCenter();

	void setCenter(sf::Vector2f center);

	sf::Vector2f getMin();
	sf::Vector2f getMax();
	sf::Vector2f getSize();

	sf::Vector2f closestPointOnBoundsToPoint(sf::Vector2f boundingBox);

	AABB minkowskiDifference(AABB *other);

private:
	void initialise();

	float m_x, m_y, m_width, m_height;
	sf::Vector2f m_center, m_extends, m_min, m_max, m_size;
};

#endif // !AABB_H

/*
class AABB
{
	public var center:Vector = new Vector();
	public var extents:Vector = new Vector();
	public var min(get, never):Vector;
	public function get_min()
	{
		return new Vector(center.x - extents.x, center.y - extents.y);
	}
	public var max(get, never):Vector;
	public function get_max()
	{
		return new Vector(center.x + extents.x, center.y + extents.y);
	}
	public var size(get, never):Vector;
	public function get_size()
	{
		return new Vector(extents.x * 2, extents.y * 2);
	}

	public function new(center:Vector, extents:Vector)
	{
		this.center = center;
		this.extents = extents;
	}

	public function minkowskiDifference(other:AABB):AABB
	{
		var topLeft:Vector = min - other.max;
		var fullSize:Vector = size + other.size;
		return new AABB(topLeft + (fullSize / 2), fullSize / 2);
	}
}*/

/*
// (in the AABB class)
public function closestPointOnBoundsToPoint(point:Vector):Vector
{
	var minDist:Float = Math.abs(point.x - min.x);
	var boundsPoint:Vector = new Vector(min.x, point.y);
	if (Math.abs(max.x - point.x) < minDist)
	{
		minDist = Math.abs(max.x - point.x);
		boundsPoint = new Vector(max.x, point.y);
	}
	if (Math.abs(max.y - point.y) < minDist)
	{
		minDist = Math.abs(max.y - point.y);
		boundsPoint = new Vector(point.x, max.y);
	}
	if (Math.abs(min.y - point.y) < minDist)
	{
		minDist = Math.abs(min.y - point.y);
		boundsPoint = new Vector(point.x, min.y);
	}
	return boundsPoint;
}

...
// (elsewhere)
var penetrationVector:Vector = md.closestPointOnBoundsToPoint(Vector.zero);

...
boxA.center += penetrationVector;
*/