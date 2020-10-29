test : test_double_linked_list test_permutations
test_double_linked_list: double_linked_list
	@echo "=== test_double_linked_list ==="
	./double_linked_list | more
	@echo "==============================="
test_permutations: permutations
	@echo "=== test_permutations  ========"
	./permutations 1 1 | more
	@echo "-------------------------------"
	./permutations 2 1 | more
	@echo "-------------------------------"
	./permutations 2 2 | more
	@echo "-------------------------------"
	./permutations 3 1 | more
	@echo "-------------------------------"
	./permutations 3 2 | more
	@echo "-------------------------------"
	./ permutations 3 3 | more
	@echo "==============================="
double_linked_list : double_linked_list.c
	gcc -o double_linked_list double_linked_list.c
permutations : permutations.c
	gcc -o permutations permutations.c
clean :
	rm double_linked_list
	rm permutations
