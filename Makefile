CC=gcc
make:
	gcc virus_scanner.c -o virus_scanner -lcrypto
	./virus_scanner		
