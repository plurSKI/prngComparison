all: clockDrift xorFiles parseNumbers aesRng

clockDrift: clockDrift.c
	gcc -o clockDrift clockDrift.c

xorFiles: xorFiles.c
	gcc -o xorFiles xorFiles.c

parseNumbers: parseNumbers.c
	gcc -o parseNumbers parseNumbers.c

aesRng: aesRng.c
	gcc -o aesRng aesRng.c -lgcrypt

clean:
	rm clockDrift xorFiles aesRng parseNumbers

