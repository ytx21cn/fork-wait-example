name = fork-wait

all: $(name).out

$(name).out: $(name).c
	gcc -g -Wall -Werror $(name).c -o $(name).out

clean:
	rm *.out
