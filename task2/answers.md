## Ile procesów powstanie przy n-krotnym wywolaniu funkcji fork-exec jak wyżej i dlaczego?
Przy n-krotnym wywolaniu funkcji fork-exec powstanie n procesów. Powodem takiego zachowania jest działanie polecenia exec, które zastępuje obecnie działający
program na ten, podany przez użytkownika.
