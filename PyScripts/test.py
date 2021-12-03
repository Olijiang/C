from turtle import *
import time


def init():
    setup(1200,800,450,150) #设置画布大小 1200 8200 为屏幕位置
    colormode(255)
    speed(10.4)
    ht() 
    pu()
    pensize(15)
    pencolor('pink')
    
    goto(-450,150)

def reset():
    clear()
    penup()
    goto(-450,150)

def DrawNumber(i):
    if i in [2,3,5,6,7,8,9,0]: pendown()
    else:penup()
    seth(0)
    fd(100)
    
    if i in [2,3,4,7,8,9,0]: pendown()
    else:penup()
    seth(-90)
    fd(100)
    
    if i in [3,4,5,6,7,8,9,0]: pendown()
    else:penup()
    fd(100)
    
    if i in [2,3,5,6,8,9,0]: pendown()
    else:penup()
    seth(-180)
    fd(100)
    
    if i in [1,2,6,8,0]: pendown()
    else:penup()
    seth(90)
    fd(100)
    
    if i in [2,3,4,5,6,8,9]: pendown()
    else:penup()
    seth(0)
    fd(100)
    penup()
    seth(180)
    fd(100)
    pendown()

    if i in [1,4,5,6,8,9,0]: pendown()
    else:penup()
    seth(90)
    fd(100)
    penup()
    seth(0)
    fd(150)
    pendown()

def DrawDot():
    penup()
    seth(-90)
    fd(50)
    dot(15)
    fd(100)
    dot(15)
    seth(90)
    fd(150)
    seth(0)
    fd(50)



def main():
    init()
    start = time.perf_counter()
    end = time.perf_counter()
    timegap = int(end-start)
    settime = 60
    while(timegap<=settime):
        tracer(False)
        hour = timegap/3600
        minute = timegap%3600/60
        second = timegap%60
        DrawNumber(int(hour))
        DrawDot()
        DrawNumber(int(minute/10))
        DrawNumber(int(minute%10))
        DrawDot()
        DrawNumber(int(second/10))
        DrawNumber(int(second%10))
        end = time.perf_counter()
        timegap = int(end-start)
        tracer(True)
        time.sleep(0.5)
        reset()
    done()


main()