#include "ball.h"
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <ctime>
#include <chrono>
#include <iostream>
#include <QKeyEvent>

MyWidget::MyWidget(const QString &title) : QWidget(nullptr)
{
    std::srand(std::time(NULL));
    setWindowTitle(tr("Random Ball striking each other...."));

    int c = rand() % 255, d = rand() % 255, e = rand() % 255;
    timer = new QTimer;
    for (int i = 0; i < NO_BALLS - 1; ++i)
    {
        allball[i].mycolor = QColor(rand() % 255, rand() % 255, rand() % 255);
        allball[i].centre = Point(rand() % 1800 + 40, rand() % 900 + 50);
        allball[i].current_direction = vector(rand() % 50 - 20, rand() % 50 - 20);
        allball[i].radius = 5;
    }
    allball[NO_BALLS-1].mycolor = QColor(rand() % 255, rand() % 255, rand() % 255);
    allball[NO_BALLS-1].centre = Point(rand() % 1800 + 40, rand() % 900 + 50);
    allball[NO_BALLS-1].current_direction = vector(0,0);
    allball[NO_BALLS-1].radius = 100;
    connect(timer, &QTimer::timeout, this, &MyWidget::UpdatePaint);
    for(int i = 0; i < MAX_TRACER; ++i)
    {
        PathTracer[i].x = 0;
        PathTracer[i].y = 0;
    }
    timer->start(20);

    for(int i = 0; i < MAX_TRACER; ++i)
    {
        PathTracer[i] = allball[NO_BALLS-1].centre;
    }
}
void MyWidget::UpdatePaint()
{
    head_path = (head_path+1)%(MAX_TRACER);
    tail_path = (tail_path+1)%(MAX_TRACER);
    auto start = std::chrono::steady_clock::now();
    CheckForCollision();
    CheckBallCollision();
    CalculatePosition();
    PathTracer[head_path] = allball[NO_BALLS-1].centre;
    auto mid = std::chrono::steady_clock::now();
    // std::cout << "FPS is : " << std::chrono::duration_cast<std::chrono::microseconds>(mid-start).count();
    update();
    auto end = std::chrono::steady_clock::now();
    auto interval = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    // std::cout << "FPS is : " << std::pow(10, 6) / interval << '\n';
}

void MyWidget::RenderBalls()
{
    for (int i = 0; i < NO_BALLS; ++i)
    {
        painter->setBrush(QBrush(allball[i].mycolor));
        painter->drawEllipse(QPoint((int)allball[i].centre.x, (int)allball[i].centre.y), allball[i].radius, allball[i].radius);
    }
}

void MyWidget::RenderPaths()
{
    auto j = (tail_path+1)%MAX_TRACER;
    QPen pen1;
    pen1.setWidth(4);
    painter->setPen(std::move(pen1));
    for(int i = tail_path; i!=head_path; i = j)
    {
        j = (i+1)%MAX_TRACER;
        painter->drawLine(PathTracer[i].x, PathTracer[i].y,PathTracer[j].x,PathTracer[j].y);
    }
    painter->setPen(QPen());
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    RenderBalls();
    RenderPaths();
    painter->end();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MyWidget *frame = new MyWidget("What's up Rowdy...");
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    frame->setPalette(palette);
    frame->setAutoFillBackground(true);
    // frame->showMaximized();
    frame->showFullScreen();
    return app.exec();
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        exit(1);
    }
}