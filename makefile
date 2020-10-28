test : a.out
	@echo "==============================="
	./a.out 1 1 | more
	@echo "==============================="
	./a.out 2 1 | more
	@echo "==============================="
	./a.out 2 2 | more
	@echo "==============================="
	./a.out 3 1 | more
	@echo "==============================="
	./a.out 3 2 | more
	@echo "==============================="
	./a.out 3 3 | more
	@echo "==============================="
a.out : permutations.c
	gcc permutations.c
clean :
	rm a.out
