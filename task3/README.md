# =====================================================
# Kamil Kuziora                       Kraków 30.03.2022
# =====================================================

# Ćwiczenie 3 
Celem tego projektu są działania związane z obsługą procesów.

## Uruchamianie
1. Użyj polecenia `make run [task_name] HM="[sposób obsługi sygnału: 0 - default, 1 - ignore, 2 - custom] PN="[signal]"`  
2. Użyj polecenia `./[task_name] [sposób obsługi sygnału: 0 - default, 1 - ignore, 2 - custom] [signal]`

## Struktura projektu
```
├── bin
│   ├── task_a
│   ├── task_b
│   ├── task_c
│   └── task_c2
├── Makefile
├── obj
│   ├── task_a.o
│   ├── task_b.o
│   ├── task_c2.o
│   ├── task_c.o
│   └── utils.o
├── README.md
└── src
    ├── task_a.c           
    ├── task_b.c
    ├── task_c2.c
    ├── task_c.c
    ├── utils.c             # zawiera funkcję do wczytywania wejścia od użytkownika
    └── utils.h 
```

## Makefile
- samo wywołanie komendy make powoduje skompilowanie plików źródłowych 
- make clean
- make tar 
