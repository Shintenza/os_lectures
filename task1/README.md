# ========================================================================
# Kamil Kuziora                                          Kraków 17.03.2022
# ========================================================================

# Struktura katalogu

```
├── answers.md          // odpowiedzi na pytania
├── bin                 // katalog powstaje po wywołaniu make i zawiera pliki binarne
│   ├── task_a
│   ├── task_b
│   ├── task_c
│   ├── task_d
│   └── task_e
├── Makefile
├── obj                 // katalog powstaje po wywołaniu make i zawiera pliki obiektowe
│   ├── task_a.o
│   ├── task_b.o
│   ├── task_c.o
│   ├── task_d.o
│   └── task_e.o
├── README.md
└── src                 // katalog zawiera kody źródłowe rozwiązań
    ├── task_a.c
    ├── task_b.c
    ├── task_c.c
    ├── task_d.c
    └── task_e.c
```

# Makefile
- samo wywołanie komendy make powoduje skompilowanie plików źródłowych 
- make run [nazwa_zadania] - powoduje uruchomienie pliku binarnego o podanej nazwie (dostępne nazwy: od task_a do task_e); przykładowe użycie: *make run task_a*
- make clean
- make tar 
