all: mypro
  
mypro: mypro.c
	gcc -o mypro mypro.c
  
clean:
	rm mypro