# 2D_BallCollision
Simulation of Random Ball Colliding in 2 dimensio with perfect elastic collision <br>
Qt version used : 5.12.5 <br>
qmake --version : 3.1<br>
<br>
Don't forget to add QT += gui widgets in (projectname).pro after initializing with qmake -project <br>
  <br>
  Not much to say .. Source code is poorly documented. So bear with it.
  
<br><br> Note : By no means, it has no bug or glitch, it just works.
<br>
For windows users, you have to build it yourself through Qt Creator or qmake+nmake ... Qt doesn't build static executable files.
It dispatches executables dynamically (unless built qt statically -_- -_-).

<br>
<br>
**# Brownian Motion**
<br>
For 2D elastic collision, we have assumed 
<br> m1/m2 = (r1/r2)^2 <br> For sphere, it might be (r1/r2)^3.
<br>
<br> Change NO_BALLS macro to adjust the number of small balls.
<br> Enough balls may slow down the movement (drop fps).
<br> Macro MAX_TRACER (if it is), adjusts how long path is traced ( MAX_TRACER/50 seconds). If it is 800, roughly 16s will be traced before path erased itself from the tail. It can be increased though, with little affect in performance.
<br>
<br>
This program could be optimized like crazy(especially the collision detection part). BST (RB or AVL) can be used to speed up collision detection algorithm by a huge factor.
<br>
