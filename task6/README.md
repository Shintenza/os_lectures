# Kamil Kuziora                       Kraków 30.04.2022


## Ćwiczenie 4
Implementacja wzajemnego wykluczania się procesów za pomocą semaforów nazwanych standardu POSIX

## Uruchamianie
1. Użyj polecenia `make run main`  

## Struktura projektu
```
├── bin
│   ├── exclusion
│   └── main
├── Makefile        
├── obj
│   ├── exclusion.o
│   ├── file_handlers.o
│   ├── main.o
│   └── sem_handlers.o
├── README.md
└── src
    ├── exclusion.c                 #implementacja wzajemnego wykluczania się
    ├── file_handlers.c             #zestaw funkcji do obsługi plików
    ├── include                     #pliki nagłówkowe
    │   ├── file_handlers.h     
    │   └── sem_handlers.h
    ├── main.c                      #główny program tworzący potomne, uruchamiające algorytm wzajemnego wykluczania się 
    └── sem_handlers.c              #zestaw funkcji do obsługi semaforów
```
