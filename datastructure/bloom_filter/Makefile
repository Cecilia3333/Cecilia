.PHONY:clean

bloom_filter:bitmap.c test.c bloom_filter.c hash_func.c
	gcc -o $@ $^

clean: 
	rm -f bloom_filter
