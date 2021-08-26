import time, random, threading

Stime = time.perf_counter()



first = 1
rear = 1

class producer():
    
    def creat(self):
        global first
        global rear
        a = random.random()
        time.sleep(a)
        if(first>rear+1):
            print("%.2f Cat:还有呢，吃完再说"%(time.perf_counter()-Stime))
        else:
            print("%0.2f Cat:生成了大饼%d"%(time.perf_counter()-Stime,first))
            first+=1

class consumer():
    def eat(self):
        global rear
        b = random.random()*2
        time.sleep(b)
        if(rear<first):
            print("%0.2f Dog:我吃了大饼%d"%((time.perf_counter()-Stime),rear))
            rear+=1
        else:
            print("%0.2f Dog:快要饿死人啦"%(time.perf_counter()-Stime))

cat = producer()
dog = consumer()

def p1():
    cat.creat()

def p2():
    dog.eat()

n=1
while(n<10):

    t1 = threading.Thread(target=p1,args=())
    t2 = threading.Thread(target=p2,args=())

    t1.start()
    t2.start()
    time.sleep(random.random())
    #t1.join()
    #t2.join() 
    n+=1
    

