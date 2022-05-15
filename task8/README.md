# Kamil Kuziora                       Kraków 14.05.2022

## Ćwiczenie 8
Implementacja problemu klient-serwer przy użyciu kolejek komunikatów standardu POSIX.

## Uruchamianie
1. Użyj polecenia `make start`

## Struktura projektu
```
├── bin
│   ├── client
│   └── server
├── Makefile
├── obj
│   ├── client.o
│   ├── msg_handlers.o
│   └── server.o
├── README.md
└── src
    ├── client.c                        #implementacja klienta
    ├── include                         #pliki nagłówkowe
    │   ├── msg_handlers.h              
    │   └── server.h
    ├── msg_handlers.c                  #zestaw funkcji do obsługi kolejek komunikatów
    └── server.c                        #implementacja serwera
```
