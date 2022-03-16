# Makefile
- samo wywołanie komendy make powoduje skompilowanie plików źródłowych 
- make run <nazwa_zadania> (np. make run task_a), powoduje uruchomienie danego programu (dostępne nazwy to task_a do task_e)
- make clean
- make tar 

# Ćwiczenie 1 - przykład d
                                        (63583,63477,63583)
                                    /           |             \
                    (63584,63583,63583) (63586, 63583, 63583)  (63585,63583,63583)
                    /               |                                 |
        (63593,63584,63583)   (63595,63584,63583)             (63594,63585,63583)
                |
        (63616,63593,63583)


# Ile procesów powstanie przy n-krotnym wywolaniu funkcji fork i dlaczego?
Odp: 2^n; jest tak, ponieważ każdorazowe wywołanie funkcji fork powoduje duplikat procesu-rodzica. W powyższym przypadu wywołaliśmy funkcję fork 3 razy
co dało nam całkowitą liczbę procesów równą 2^3=8.
