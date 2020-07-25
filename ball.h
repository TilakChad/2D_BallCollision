#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>
#include <QColor>
#include <cmath>
#include <QTimer>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

constexpr float pi = 3.141592;
constexpr int ballsNumber = 10;

class QTimer;
class QPainter;

struct vector
{
    float i;
    float j;
    vector() : i{0},j{0} { }
    vector(float i, float j) : i{i},j{j} { }
    float angle();
    float magnitude();
    vector unitvector()
    {
        if(magnitude()==0)
            return vector(0,0);
        else
            return vector(i/magnitude(),j/magnitude());
    }
    float dotproduct(vector a)
    {
        return a.i*i+a.j*j;
    }

};

struct Point
{
    float x,y;
    Point() : x{0},y{0} { }
    Point(float x, float y) : x{x}, y{y} { }
    vector operator-(Point b)
    {
        return vector(x-b.x,y-b.y);
    }
};

struct Ball
{
    int radius = 35;
    Point centre = {0,0};
    Ball() = default;
    Ball(Point a, int r) : radius{r},centre{a} { }

    float speed = 0;
    QColor mycolor;
    vector current_direction;
};

class MyWidget : public QWidget
{
    Q_OBJECT;
public:
    MyWidget(const QString& );
    void paintEvent(QPaintEvent* );
    void RenderBalls();
    void CalculatePosition();
    void CheckForCollision();
    void CheckBallCollision();
    void CalculateNewVectors(Ball& a, Ball& b);
    Ball allball[20];
private:
    QTimer *timer;
    QPainter* painter;
public slots:
    void UpdatePaint();
};

#endif