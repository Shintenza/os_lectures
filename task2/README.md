# =====================================================
# Kamil Kuziora                       Kraków 20.03.2022
# =====================================================

# Ćwiczenie 2

Zadaniem programu jest wywolanie funkcji fork n-krotnie i uzycie funkcji exec do wywolania innego programu, ktory wypisze informace o potomnym procesie

## Uruchamianie
1. Użyj polecenia `make run task2 ARGS="task2_out"` 
2. Użyj polecenia `cd bin && ./task2 task2_out`

Brak dodatkowych argumentów podczas wywołania powoduje użycie polecenia echo do wyświetlenia informacji w procesie potomnym

## Struktura projektu

```
├── answers.md
├── bin
│   ├── task2
│   └── task2_out
├── Makefile
├── obj
│   ├── task2.o
│   └── task2_out.o
├── README.md
└── src
    ├── task2.c         # kod źródłowy rozwiązania
    └── task2_out.c     # prosty program do wyświetlania zadanej mu wiadomości jako argument
```

## Makefile
- samo wywołanie komendy make powoduje skompilowanie plików źródłowych 
- make clean
- make tar 
