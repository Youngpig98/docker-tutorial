all: image

mem_alloc: mem-alloc/mem_alloc.c
	gcc -o mem-alloc/mem_alloc mem-alloc/mem_alloc.c
read_file: read-file/read_file.c
	gcc -o read-file/read_file read-file/read_file.c
write_file: write-file/write-file.c
	gcc -o write-file/write_file write-file/write-file.c
image: mem_alloc read_file
	docker build -t youngpig/page_cache_test:v1 .
clean:
	rm mem-alloc/mem_alloc -f
	rm read-file/read_file -f
	docker rmi youngpig/page_cache_test:v1

write: write_file
	docker build -t youngpig/page_cache_test:v2 -f Dockerfile_write .
