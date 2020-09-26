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
    for (int i = 0; i < NO_BALLS; ++i)
    {
        allball[i].centre.x += allball[i].current_direction.i;
        allball[i].centre.y += allball[i].current_direction.j;
    }
}

void MyWidget::CheckForCollision()
{
    for (int i = 0; i < NO_BALLS; ++i)
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
    for (int i = 0; i < NO_BALLS; ++i)
    {
        for (int j = i + 1; j < NO_BALLS; ++j)
        {
            x = allball[i].centre.x - allball[j].centre.x;
            y = allball[i].centre.y - allball[j].centre.y;
            distance = x * x + y * y;
            if (allball[i].radius == allball[j].radius && distance <= 10 * 10)
            {
                CalculateNewVectors(allball[i], allball[j]);
            }
            else if (i == NO_BALLS - 1 || j == NO_BALLS - 1)
            {
                if (distance <= ((allball[i].radius + allball[j].radius) * (allball[i].radius + allball[j].radius)))
                {
                    CalculateNewVectors(allball[i], allball[j]);
                }
            }
        }
    }
}

void MyWidget::CalculateNewVectors(Ball &a, Ball &b)
{
    vector centre = vector{a.centre.x - b.centre.x, a.centre.y - b.centre.y};
    vector normalunit = centre.unitvector();

    vector tangentunit = vector(-normalunit.j, normalunit.i);
    float atan1, btan1;

    atan1 = a.current_direction.dotproduct(tangentunit);
    btan1 = b.current_direction.dotproduct(tangentunit);

    float anorm1, bnorm1;
    anorm1 = a.current_direction.dotproduct(normalunit);
    bnorm1 = b.current_direction.dotproduct(normalunit);

    float amag, bmag;
    if (a.radius == b.radius)
    {
        bmag = anorm1;
        amag = bnorm1;
    }
    else
    {
        auto constant = (float(a.radius) / b.radius) * (float(a.radius) / b.radius);

        amag = (constant - 1) / (constant + 1) * anorm1 + 2 / (constant + 1) * bnorm1;

        bmag = 2 * constant / (constant + 1) * anorm1 + (1 - constant) / (1 + constant) * bnorm1;

    }

    a.current_direction = vector{atan1 * tangentunit.i + amag * normalunit.i, atan1 * tangentunit.j + amag * normalunit.j};
    b.current_direction = vector{btan1 * tangentunit.i + bmag * normalunit.i, btan1 * tangentunit.j + bmag * normalunit.j};
}
