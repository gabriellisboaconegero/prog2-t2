CFLAGS = -std=c99 -Wall
O_FILES = beale.o lista.o chave.o codifica.o decodifica.o lista_chave.o

%.o: %.c %.h
	gcc $(CFLAGS) -c $< -o $@

all: beale

beale: $(O_FILES)
	gcc $^ -o beale

beale.o: beale.c
	gcc $(CFLAGS) -c $< -o $@

teste: teste.c
	gcc $< -o $@ $(CFLAGS)

purge: clean
	rm -rf beale

clean:
	rm -rf *.o *.txt
