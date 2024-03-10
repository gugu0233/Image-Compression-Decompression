main.c

  Incep prin a utiliza parametrii in linia de comanda, conform cerintei. Daca al doilea argument (argv[1]) 
este c1 sau c2 (adica cerinta 1 sau 2), atunci urmatorul argument va fi factorul, pe care il convertesc din 
string in int cu ajutorul functiei "atoi", al patrulea argument este fisierul din care citesc, iar al cincilea 
este fisierul in care afisez. Daca al doilea argument este d, atunci al treilea argument va fi fisierul de intrare
si al patrulea cel de iesire. Dupa ce verific daca fisierele de intrare si de iesire au fost deschise cu 
succes, citesc antetul fisierului de intrare: tipul P6, dimensiunile imaginii si valoarea maximă pe care o 
poate lua o culoare. Apoi, aloc memorie si citesc informatiile despre pixeli, dupa care creez cate o matrice 
patratica pentru ficare culoare in parte, folosind vectori de pointeri. Dupa ce am alocat matricele, separ 
pixelii pe culori si umplu corespunzator fiecare matrice.
  Folosesc functia "divizare" pentru a crea arborele de compresie si incep rezolvarea pentru fiecare cerinta.
Pentru cerinta 1, printez in fisierul de iesire numarul de niveluri din arbore, cu ajutorul functiei "nrniv".
Apoi, printez numarul de frunze, pe care il aflu cu functia "nrfrunze" si la final, printez dimensiunea 
laturii pătratului pentru cea mai mare zonă din imagine care a rămas nedivizată impartind dimensiunea imaginii 
de atatea ori cate niveluri sunt in arbore.
   Pentru cerinta a doua, scriu in fisierul comprimat in format binar dimensiunea si nodurile din arbore 
conform cerintei, cu ajutorul functiei "noduriniv".
   La final, eliberez memoria alocata si inchid fisierele.

functiiArb.c

   Functia "ConstrNod" creeaza un nod cu 4 fii si cu informatia x si intoarce adresa acestuia.
   Functia "distruge" distruge toate nodurile in arbore, distrugand fiecare subarbore in parte, apoi nodul 
radacina.
   Functia "DistrArb" distruge toate nodurile arborelui de la o adresa si lasa arborele vid.
   Functia "medie" calculeaza media aritmetică a valorilor din submatricea de pixeli care corespunde unui 
anumit bloc, folosind formula data in cerinta.
   Functia "calcMEAN" calculează un scor al similaritătii pentru blocul respectiv, folosind formula data.
   Functia "nrfrunze" returneaza numarul de frunze, parcurgand recursiv arborele.
   Functia "max_of_four" returneaza maximul dintre 4 nr.
   Functia "nrniv" returneaza nr de niveluri din arbore, pe care il parcurge recursiv pe fiecare parte.
   Functia "min_of_four" returneaza minimul dintre 4 nr.
   Functia "detniv" returneaza nivelul pe care se afla prima frunza in arbore.
   Functia "divizare" returneaza arborele de compresie. Daca scorul este mai mic sau egal ca factorul dat, 
atunci nodul ia valoarea 1, ceea ce inseamna ca este frunza, iar fiecare componenta de culoare primeste valoarea 
mediei aritmetice a valorilor din submatricea de pixeli. Altfel, continui divizarea, impartind matricea pe 
jumatate si parcurgand cele patru zone.
   Functia "noduriniv" scrie in fisierul de compresie nodurile de pe un nivel. Intai scriu tipul, apoi daca 
este frunza, scriu valorile pentru fiecare culoare in parte. Daca nu sunt pe nivelul cautat, cresc nivelul curent.
