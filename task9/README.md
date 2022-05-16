# Kamil Kuziora                       Kraków 16.05.2022

## Ćwiczenie 8
Implementacja problemu wzajemnego wykluczania się wątków. W ćwiczeniu stosowane są muteksy, służące do synchronizacji wątków. Jako test poprawnej synchronizacji,
inkrementowana jest zmienna globalna, a następnie porównywana z oczekiwanym wynikiem (liczba sekcji krytycznych * liczba wątków).

## Uruchamianie
1. Użyj polecenia `make run`
2. Ilość sekcji krytycznych można zmienić za pomocą zmiennych `PROC_N` i `CRYT_N` w pliku `Makefile`

## Struktura projektu
```
├── Makefile
├── README.md
└── src
    ├── exclusion.c             #plik źródłowy zawierający implementację wykluczania się wątków
    ├── include                 #pliki nagłówkowe
    │   └── exclusion.h
    └── main.c                  #tworzenie muteksu, wątków
```
