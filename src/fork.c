#include <stdlib.h>
#include <stdio.h>

int a = 0;
pid_t pp;

int main() {
	printf("Program demonstrujacy funkcje fork()\n\n");
	
	if(pp != 0)	
		a = 666;
	pp = fork();

	if(pp == 0){
		printf("Child %d\n", a);
	}else{
		printf("Matka\n");
		a=666;
	}


/*
	// rozdzielamy sie, od tego momentu beda istnialy dwa procesy wykonujace dalsza czesc kodu (w funkcja fork() wlacznie)
	pid_t pidFork = fork();

	// pobieramy identyfikator procesu (PID)
	pid_t pidProcesu = getpid();

	// ta wiadomosc powinna sie wyswietlic podwojnie, ale z roznymi PID
	printf("Ta wiadomosc powinna wyswietlic sie dwa razy, wyswietlenie dla procesu o pid = %d\n", pidProcesu);
	
	if (pidFork == 0) {
		printf("---> Jestem procesem potomnym, moj pid = %d\n", pidProcesu);
	} else {
		// jezeli wynik zwrocony przez fork() jest rozny od zera, to jestesmy nadal w procesie macierzystym
		printf("---> Jestem procesem macierzystym, moj pid = %d\n", pidProcesu);
	}
*/
	return EXIT_SUCCESS;
}
