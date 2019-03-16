									Tema 1 EGC
								  BRICK BREAKER 
								     Jorascu Marian Vladut 325CC


TOATE SURSELE SUNT IN FISIERUL "Laborator1" 

In Tema realizata de mine se va folosi doar Mouse-ul cu specificatiile din enunt.
Pentru a lansa bila trbuie sa fie apasat click stanga, iar platforma se misca
cu ajutorul mouse-lui.

Bila atunci cand se ciocneste de pereti / caramizi / platforma
Se reflecta exact ca in enunt .
Mentionez faptul ca autunci cand bila se ciocneste cu "varful unei caramizi" aceasta
se intoarce pe aceeasi directie pe care a venit , dar in sens opus

Am implementat toate cerintele temei precizate in enunt. 
Ca si super-puteri:
1. Powerup1 - cand platforma reuseste sa "prinda" un powerup albastru bila se face de doua 
ori mai mare (se dubleaza raza) pentru 30 de secunde , de la ultimul powerup albastru, acest
timp nu se cumuleaza . Cronometrul de superputere se "reseteaza" la fiecare bila de o culoare
prinsa ( acest lucru este valabil pentru toate superputerile).

2. Powerup2 - cand platforma reusete sa "prinda" un powerup galben bila devine invincibila si
timp de 30 de secunde aceasta va distruge orice caramida din prima ( trece prin ele).

3.Powerup3 - cand platforma reusete sa "prinda" un powerup rosu se mai adauga timp de 30 de secunde
un perete in partea de jos.

4.De fiecare data cand platforma reusete sa prinda o superputere , cat timp aceasta are valabilitate
(nu au trecut cele 30 de secunde) bara va avea culoarea superputerii. De fiecare dataa va avea culoarea
ultimului powerup prins. De asemenea atat platforma cat si peretii ( 3 sau 4) vor prelua culoarea repsectiva.

5. Fiecare caramida are 4 "vieti" , cu alte cuvinte ea trebuie lovita de 4 ori pentru a fi distrusa. Din pacate
aceste vieti nu mai sunt folositoare atunci cand este activata puterea care ii permite bilei sa nu isi mai schimbe
directia la coliziunea cu o caramida. De fiecare data cand este lovita se schimba culoarea ( se deschide din
ce in ce mai tare)


PS:
Stiu ca nu este cea mai OOP implementare (chiar daca am folosit destule clase , dar nu am 
respectat toate principiile(sa fac membrii private/protected ...)). In apararea mea mentionez faptul ca m-am apucat
taziu de tema si mi-a fost frica ca daca o sa stau sa scriu OOP nu voi avea timp
sa termin tema in timp util.