all:
	gcc main.c -o carga
	@echo "Uso:"
	@echo "   './carga | lp_solve'"
	@echo "   Ou: '{entrada} | ./carga | lp_solve'"
clean:
	rm carga
