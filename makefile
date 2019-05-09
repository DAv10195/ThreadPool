compile1:
	gcc *.h test1.c threadPool.c osqueue.c -pthread
compile2:
	gcc *.h test2.c threadPool.c osqueue.c -pthread
run:
	./a.out
