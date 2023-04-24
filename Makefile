CFLAGS = -std=c99 -Wall
O_FILES = beale.o lista.o chave.o codificacao.o

%.o: %.c %.h
	gcc $(CFLAGS) -c $< -o $@

all: beale

beale: $(O_FILES)
	gcc $^ -o beale

obeale.o: beale.c
	gcc $(CFLAGS) -c $< -o $@

teste: teste.c
	gcc $< -o $@ $(CFLAGS)

purge: clean
	rm -rf beale

clean:
	rm -rf *.o *.txt
