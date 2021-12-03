from turtle import*

from time import*

from random import*

def yesgo():
    p = 20
    s = pow(2,1/2)
    begin_fill()
    lt(45)
    fd(p)
    rt(45)
    fd(40*s)
    rt(45)
    fd(p)
    rt(90)
    fd(p)
    rt(45)
    fd(40*s)
    rt(45)
    fd(p)
    rt(135)
    fillcolor(randint(25,255),randint(25,255),randint(25,255))
    end_fill()
    pu()
    fd(60*s+5)
    rt(90)
    fd(5)
    pd()

def nogo():
    pu()
    p = 20
    s = pow(2,1/2)
    fd(60*s+5)
    rt(90)
    fd(5)
    pd()

def ifgo(d):
    yesgo() if d in [2,3,4,5,6,8,9] else nogo()
    yesgo() if d in [0,1,3,4,5,6,7,8,9] else nogo()
    yesgo() if d in [0,2,3,5,6,8,9] else nogo()
    yesgo() if d in [0,2,6,8] else nogo()
    pu()
    bk(5)
    lt(90)
    fd(5)
    pd()
    yesgo() if d in [0,4,5,6,8,9] else nogo()
    yesgo() if d in [0,2,3,5,6,7,8,9] else nogo()
    yesgo() if d in [0,1,2,3,4,7,8,9] else nogo()
 
def wait():
    sleep(1)
    
def main():
    setup(800,350,200,200)
    colormode(255)
    ht()
    pu()
    fd(-100)
    pd()
    st()
    speed(10.4)
    q = pow(2,1/2)
    for i in range(5,0,-1):
        ht()
        tracer(False)
        ifgo(i)
        pu()
        fd(60*q)
        rt(180)
        pd()
        tracer(True)
        wait()
        clear()
    tracer(False)
    ifgo(0)
    tracer(True)
    hideturtle()
    wait()
    clear()
    pencolor('pink')
    write('完美',align='center',font=('Arial',100,'normal'))
    hideturtle()
    done()

main()