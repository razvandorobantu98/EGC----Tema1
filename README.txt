Dorobantu Razvan-Florin, 335CB

===============================================================================
Fisiere:

Pentru implementarea temei am folosit scheletul Laboratorului 3.
In fisierul Transformari2D.h am scris functiile care returneaza matricile de 
translatie, scalare si rotatie.
In fisierul Obiecte2D.cpp  am scris functiile care creeaza meshuri in forma de 
patrat, cerc si triunghi.
In Tema1.cpp am implementat tema propriu-zisa. 

===============================================================================
Miscarea pasarii:

Am construit pasarea din 3 cercuri (ochi, cap si corp) si 2 triunghiuri (cioc 
si coada) de marimi si culori diferite.
La inceput translatez pasarea intr-un punct initial (birdInitialX, 
birdInitialY).
Factorul de translatie a pasarii pe axa OY depinde de variabila speed.
Daca speed este pozitiva atunci translatia se face in sensul axel OY, iar daca 
este negativa se face in sens invers.
Aceasta creste brusc in momentul in care apas Space, si astfel pasarea sare. 
Daca nu se apasa Space, valoarea scade la fiecare frame si pasarea cade.
Calculez matricea de rotatie fata de punctul ce reprezinta centrul de greutate 
al pasarii, si rotesc cu +0.5 sau -0.5 radiani, in functie de semnul variabilei 
speed.

===============================================================================

Miscarea obstacolelor:

Un obstacol este compus din 2 patrate scalate neuniform, unul reprezentand 
pipe-ul propriu-zis si celalalt reprezantand capacul.
Intotdeauna vor exista 5 obstacole, 4 desenate pe ecran si unul in afara 
ecranului (pentru a da impresia de continuitate).
In variabila levelPosition retin pozitia pe axa OX a primului obstacol (cel mai
din stanga). Intre obstacole se pastreaza o distanta fixa (widthSection). 
Astfel, al doilea obstacol va fi la pozitia levelPosition + widthSection, etc.
Atunci cand primul obstacol iese din ecran, urmatorul obstacol va deveni primul.
(levelPosition += widthSection).

Dimensiunile obstacolelor sunt pastrate intr-o coada. De firecare data cand 
primul obstacol iese din ecran, se scoate din coada prima valoare si se adauga 
la sfarsit o noua valoare generata random, reprezentand dimensiunea noului 
obstacol ce urmeaza sa fie creeat.

Pentru fiecare pereche de obstacole, cel de sus este translatat in marginea de 
sus a ecranului si este scalat cu o anumita dimensiune, iar cel de jos e 
translatat la marginea de jos a ecranului si scalat cu o dimensiune 
complementara. Astfel, intre obstacole se pastreaza o distanta exacta.

Pentru culoare am folosit o alta coada, cu acelasi principiu.
Cea de-a treia coada contine valori 0 sau 1, si retine daca o pereche de 
obstacole sunt glisante. Obstacolele glisante se deplaseaza cu factorul de 
translatie deltaYPipe, ce creste si scade alternativ.

===============================================================================
Coliziunea:

Am aproximat pasarea cu un dreptunghi. De fiecare data cand prima pereche de 
obstacole ajunge in dreptul pasarii (pe axa OX), verific daca dreptunghiul 
pasarii se intersecteaza cu dreptunghiurile perechii de obstacole.
In acest caz, jocul se opreste.

Daca obstacolele sunt glisante, voi lua in calcul si factorul de translatie 
deltaYPipe.
Jocul se opreste si in cazul in care pasarea cade sub marginea de jos a 
ecranului.

===============================================================================
Functionalitate joc:

La inceput, jocul porneste la apasarea tastei Space.
Se creeaza pe rand cate un obstacol (pe masura ce levelPosition ajunge la 0), 
si incep sa apara in ecran.
Obstacolele vor avea dimensiuni si culori random, si unele vor fi glisante.
Scorul creste de fiecare data cand pasarea trece de o pereche de obstacole, si 
se va afisa de fiecare data in consola.
Viteza cu care se deplaseaza obstacolele pe aza OX depinde si de variabila 
gameSpeed, care creste proportional cu scorul. Astfel, jocul devine din ce in 
ce mai greu pe masura ce se acumuleaza punctaj.
In momentul in care se detecteaza o coliziune, jocul se opreste, si imaginea 
"ingheata" (nu se mai realizeaza nicio ranslatie, rotatie si scalare pentru 
niciun obiect). Se afiseaza scorul obtinut, scorul maxim (si se actualizeaza, 
daca este cazul), si se asteapta apasarea tastei Space pentru restart.
