# Kamil Kuziora - Kraków 17.04.2022


## Ćwiczenie 5
Implementacja problemu producenta-konsumenta. Proces-producent odczytuje małe porcje pliku tekstowego (w różnych odstępach czasowych) i umieszcza je w potoku 
nazwanym. Proces-konsument odczytuje dane z potoku i zapisuje wszystkie pobrane informacje do pliku. 

## Uruchamianie
1. Użyj polecenia `make run handler`

## Struktura projektu
```
├── bin
│   ├── consumer
│   ├── handler
│   └── producer
├── Makefile
├── obj
│   ├── consumer.o
│   ├── handler.o
│   └── producer.o
├── payload.txt         # dane producenta
├── README.md
└── src
    ├── consumer.c      # implementacja konsumenta
    ├── handler.c       # zarządzanie producentem i konsumentem
    └── producer.c      # implementacja producenta
```
