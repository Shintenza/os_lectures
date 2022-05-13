# Kamil Kuziora                       Kraków 03.05.2022

## Ćwiczenie 7
Implementacja problemu "producenta-konsumenta" przy pomocy pamięci dzielonej. Potoki zastępujemy buforem cyklicznym. Dostęp do pamięci dzielonej synchornizujemy
semaforami. 

## Uruchamianie
1. Użyj polecenia `make run main`
2. Porównanie plików `make cmp`

## Struktura projektu
```
├── bin
│   ├── consumer
│   ├── main
│   └── producer
├── Makefile
├── obj
│   ├── consumer.o
│   ├── main.o
│   ├── mem_handlers.o
│   ├── producer.o
│   └── sem_handlers.o
├── payload.txt                         #plik źródłowy
└── src
    ├── consumer.c                      #kod źródłowy konsumenta
    ├── include                         #pliki nagłówkowe 
    │   ├── mem_handlers.h              
    │   └── sem_handlers.h              
    ├── main.c                          #główny program tworzący semafory, pamięć dzieloną; uruchamia producenta i konsumenta
    ├── mem_handlers.c                  #obsługa pamięci dzielonej
    ├── producer.c                      #producent
    └── sem_handlers.c                  #obsługa semaforów
```
## Synchronizacja wielu producentów i konsumentów

```
``#define N ?                           // Rozmiar bufora
typdef struct { ... } Towar;            // Definicja typu dla jednostek towaru
Towar bufor[N];                         // Bufor mogacy pomiescic N jednostek towaru
int wstaw = 0, wyjmij = 0;              // Pozycje wstawiania oraz wyjmowania towaru

semaphore PROD = N;                     // Semafor do wstrzymywania Producenta
semaphore KONS = 0;                     // Semafor do wstrzymywania Konsumenta
semaphore PROD_SWITCH = 1;              // Semafor pozwalający na działanie tylko jednego producenta
semaphore KONS_SWITCH = 1;              // Semafor pozwalający na działanie tylko jednego konsumenta


// Proces Producent
// ----------------
   Towar towarProd;
   while (1) {
    // Produkcja towaru
    P(PROD);                            // Opusc semafor Konsumenta
    P(PROD_SWITCH);                     // Opuść semafor pilnujący producentów
    bufor[wstaw] = towarProd;           // Umiesc towar w buforze
    wstaw = (wstaw + 1) % N;            // Przesun pozycje wstawiania o 1 dalej
    V(PROD_SWITCH);                     // Podnieś semafor pilnujący producentów
    V(KONS);                            // Podniesc semafor Konsumenta
   }


// Proces konsument
// ----------------
   Towar towarKons;
   while (1) {
    P(KONS);                            // Opusc semafor Konsumenta
    P(KONS_SWITCH);                     // Opuść semafor pilnujący klientów
    towarKons = bufor[wyjmij];          // Umiesc towar w buforze
    wstaw = (wstaw + 1) % N;            // Przesun pozycje wyjmowania o 1 dalej
    V(KONS_SWITCH);                     // Podnieś semafor pilnujący klientów
    V(PROD);                            // Podniesc semafor Konsumenta
    // Konsumpcja towaru
   }`
