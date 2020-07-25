#include "ball.h"
#include <iostream>

float vector::magnitude()
{
    return std::sqrt(i * i + j * j);
}

float vector::angle()
{
    float angle = atan(fabs(float(j) / i));
    if (i >= 0 && j >= 0)
        return angle;
    if (j > 0 && i <= 0)
        return pi - angle;
    if (j < 0 && i <= 0)
        return pi + angle;
    return 2 * pi - angle;
}

void MyWidget::CalculatePosition()
{
    for (int i = 0; i < ballsNumber; ++i)
    {
        allball[i].centre.x += allball[i].current_direction.i;
        allball[i].centre.y += allball[i].current_direction.j;
    }
}

/** This function checks for collision between balls.
 * Since it checks collision of every ball with every other balls, its complexity is quadratic.
 * But can be reduced dramatically if rectangular grid boxes are used to check for collision between nearest balls.
 * Checking for circular collision is easy easy .. Just calculate distance between two ball centres and compare
 * with sum of radius of ball1 and ball2 .. In this case, ball are identical so
 * sqrt((x1-x2)^2 + (y1-y2)^2) > radius of ball 1 + radius of ball 2.. Otherwise collision did occur 
 * Distance can't be negative, so sqrt can be removed by balancing equality for faster computation
 **/

void MyWidget::CheckForCollision()
{
    for (int i = 0; i < ballsNumber; ++i)
    {
        if (allball[i].centre.x - allball[i].radius < 0 || allball[i].centre.x + allball[i].radius > SCREEN_WIDTH)
        {
            allball[i].current_direction.i *= -1;
            if (allball[i].centre.x - allball[i].radius < 0)
            {
                allball[i].centre.x += 2;
            }
            if (allball[i].centre.x + allball[i].radius > SCREEN_WIDTH)
                allball[i].centre.x -= 2;
        }

        if (allball[i].centre.y - allball[i].radius < 0 || allball[i].centre.y + allball[i].radius > SCREEN_HEIGHT)
        {
            allball[i].current_direction.j *= -1;
            if (allball[i].centre.y - allball[i].radius < 0)
                allball[i].centre.y += 2;
            if (allball[i].centre.y + allball[i].radius > SCREEN_HEIGHT)
                allball[i].centre.y -= 2;
        }
    }
}

void MyWidget::CheckBallCollision()
{
    long long int distance;
    long long int x, y;
    for (int i = 0; i < ballsNumber; ++i)
    {
        for (int j = i + 1; j < ballsNumber; ++j)
        {
            x = allball[i].centre.x - allball[j].centre.x;
            y = allball[i].centre.y - allball[j].centre.y;
            distance = x * x + y * y;
            if (distance <= 70 * 70)
            {
                CalculateNewVectors(allball[i], allball[j]);
            }
        }
    }
}


/** Its the phase where 2 dimensional elastic collision occurs 
 *  Trying to use formulas studied in physics for 2d collision in grade 11 and 12 is -_- -_- -_-
 *  Instead vectors and projection should be used
 *  Steps
 *  Calculate unit vectors joing the centre of the balls
 *          i.e : normalunit = centre.unitvector();
 *  Calculate the tangent vector
 *          easy : just tangentunit = (-normalunit.j,normalunit.i) or (normalunit.j,-normalunit.i) ; Either way we will get tangent vector normal to normal vector joining the centre
 *  Direction of tangent vector doesn't matter here since the correct direction will be provided by dot product that follows : 
 *  Important thing to notice is that : Tangent vector of colliding ball does not change.. Its only the normal vector that change since the collision is head-on
 *  The collision occured between ball with same radius (i.e same mass), so magnitude of unit vector are just exchanged. 
 **/
 

void MyWidget::CalculateNewVectors(Ball &a, Ball &b)
{
    // centre is the vector that joins centre of the balls
    vector centre = vector{a.centre.x - b.centre.x, a.centre.y - b.centre.y};
    vector normalunit = centre.unitvector();

    // tangentunit it the vector normal to normal vector i.e vector that is perpendicular to both ball's moving direction
    vector tangentunit = vector(-normalunit.j, normalunit.i);
    float atan1, btan1;

    // Projection of vector a (ballA) and vector b (ball B) on tangent vector
    // Remember projection is simply dot product with unit vector 
    atan1 = a.current_direction.dotproduct(tangentunit);
    btan1 = b.current_direction.dotproduct(tangentunit);

    // Similarly projection on normal vector
    float anorm1, bnorm1;
    anorm1 = a.current_direction.dotproduct(normalunit);
    bnorm1 = b.current_direction.dotproduct(normalunit);

    // Normal component of  velocities are exchanged
    float amag, bmag;
    bmag = anorm1;
    amag = bnorm1;

    // Finalizing the direction of balls after collision
    a.current_direction = vector{atan1 * tangentunit.i + amag * normalunit.i, atan1 * tangentunit.j + amag * normalunit.j};
    b.current_direction = vector{btan1 * tangentunit.i + bmag * normalunit.i, btan1 * tangentunit.j + bmag * normalunit.j};
}

// Documentation may be mehhh.. but bear with it.
// Don't have time(precisely will) for proper documentation