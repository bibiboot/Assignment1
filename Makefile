warmup1: warmup1.o my402list.o check_input.o helper.o write.o 
	gcc -o warmup1 -g warmup1.o my402list.o check_input.o helper.o write.o

warmup1.o: warmup1.c my402list.c check_input.c helper.c write.c my402list.h format.h
	gcc -g -c -Wall warmup1.c my402list.c check_input.c helper.c write.c 

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c

check_input.o: check_input.c format.h
	gcc -g -c -Wall check_input.c

helper.o: helper.c format.h
	gcc -g -c -Wall helper.c

write.o: write.c format.h
	gcc -g -c -Wall write.c

clean:
	rm -f *.o warmup1 
