# IOS – Projekt 2 (2025)

Implementácia synchronizačného problému *Přívoz* (Semaforový prívoz) s využitím zdieľanej pamäte a semaforov v jazyku C.

## Obsah úlohy
- **Synchronizácia procesov** – Riadenie interakcie medzi hlavným procesom, procesom prívozu a procesmi áut (osobné a nákladné).
- **Zdieľaná pamäť** – Implementácia zdieľaných počítadiel a stavových premenných pre koordináciu procesov.
- **Semaforové riešenie** – Využitie semaforov na elimináciu aktívneho čakania pri naloďovaní, preprave a vyloďovaní áut.
- **Logika kapacity** – Nákladné auto zaberá miesto pre 3 osobné autá. Algoritmus striedavo naloďuje autá (1 nákladné, 1 osobné) do naplnenia kapacity $K$.
- **Správa zdrojov** – Korektná tvorba procesov pomocou `fork`, ošetrenie chybových stavov a uvoľňovanie systémových prostriedkov.

Projekt demonštruje pokročilú prácu s medziprocesovou komunikáciou (IPC) v systémoch Unix/Linux a vyžaduje striktné dodržiavanie poradia akcií vo výstupnom súbore `proj2.out`.

## Hodnotenie
- Získané body: **15 / 15**
