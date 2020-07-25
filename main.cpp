#include "ball.h"
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <ctime>
#include <chrono>
#include <iostream>

MyWidget::MyWidget(const QString& title) : QWidget(nullptr)
{
    std::srand(std::time(NULL));
    setWindowTitle(tr("Random Ball striking each other...."));

    // int c = rand()%255,d = rand()%255,e = rand()%255;
    timer = new QTimer;

    // ballsNumber of ball defined in ball.h are initialized with random centre,random color, random vector(both direction and velocity)
    // and with constant radius = 35;
    for(int i = 0; i < ballsNumber; ++i)
    {
        allball[i].mycolor = QColor(rand()%255,rand()%255,rand()%255);
        allball[i].centre = Point(rand()%1800+80,rand()%900+80);
        allball[i].current_direction = vector(rand()%20-10,rand()%20-10);
        allball[i].radius = 35;
    }

    // Generates timed signals for redrawing of the painting canvas
    connect(timer,&QTimer::timeout,this,&MyWidget::UpdatePaint);
    timer->start(20);
}
void MyWidget::UpdatePaint()
{
    // Uncheck if you want to check frame per sec
    // auto start = std::chrono::steady_clock::now();
    CheckForCollision();
    CheckBallCollision();
    CalculatePosition();
    // auto mid = std::chrono::steady_clock::now();
    // std::cout << "FPS is : " << std::chrono::duration_cast<std::chrono::microseconds>(mid-start).count();
    update();
    // auto end = std::chrono::steady_clock::now();
    // std::cout << ' ' << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << std::endl;
}

void MyWidget::RenderBalls()
{
    // Draws all circular balls
    for(int i = 0; i < ballsNumber; ++i)
    {
        painter->setBrush(QBrush(allball[i].mycolor));
        painter->drawEllipse(QPoint((int)allball[i].centre.x,(int)allball[i].centre.y),allball[i].radius,allball[i].radius);
    }
}

void MyWidget::paintEvent(QPaintEvent* event)
{
    painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);
    RenderBalls();
    painter->end();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MyWidget *frame = new MyWidget("What's up Rowdy...");
    QPalette palette;
    palette.setColor(QPalette::Window,Qt::white);
    frame->setPalette(palette);
    frame->setAutoFillBackground(true);
    frame->showMaximized(); // For maximized screen
    // frame->showFullScreen(); // For borderless full screen mode
    return app.exec();
}
