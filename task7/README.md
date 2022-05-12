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
