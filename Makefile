.PHONY:clean

heap:heap.c test.c
	gcc -o $@ $^

clean:
	rm -f heap
