# Kamil Kuziora                       Kraków 30.03.2022


## Ćwiczenie 4
Implementacja problemu producenta-konsumenta. Proces-producent odczytuje małe porcje pliku tekstowego (w różnych odstępach czasowych) i umieszcza je w potoku 
nienazwanym. Proces-konsument odczytuje dane z potoku i zapisuje wszystkie pobrane informacje do pliku. 

## Uruchamianie
1. Użyj polecenia `make run task IN=[nazwa_pliku_wejściowego] OUT=[nazwa_pliku_wyjściowego]`  
2. Do porównanie plików `make cmp`

## Struktura projektu
```
├── bin
│   └── task
├── Makefile
├── obj
│   └── task.o
├── payload.txt     # plik zawierjący dane wczytywanie prze konsumenta
├── README.md
└── src
    └── task.c
```
