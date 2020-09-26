#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QLabel>
#include <QColor>
#include <cmath>
#include <QTimer>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NO_BALLS 500
constexpr float pi = 3.141592;

// Addition of path tracer of the big ball
constexpr int MAX_TRACER = 800; // Traces the path for roughly six seconds @ 50 fps -> 16 frames

class QTimer;
class QPainter;
class QKeyEvent;

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
    void keyPressEvent(QKeyEvent*);
    void RenderBalls();
    void RenderPaths();
    void CalculatePosition();
    void CheckForCollision();
    void CheckBallCollision();
    void CalculateNewVectors(Ball& a, Ball& b);
    Ball allball[NO_BALLS];
    
    int tail_path = 0;
    int head_path = MAX_TRACER-1;
    Point PathTracer[MAX_TRACER];
private:
    QTimer *timer;
    QPainter* painter;
public slots:
    void UpdatePaint();
public:
    ~MyWidget()
    {
        delete painter;
        delete timer;
    }
};

#endif