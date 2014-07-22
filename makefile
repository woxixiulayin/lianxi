ifneq ($(MAKECMDGOALS), clean)
goals = $(MAKECMDGOALS)
endif
	
$(goals): $(addsuffix .c, $(goals))
	gcc -o $(goals) $< 
	$(addprefix  ./, $(goals))	
clean:
	rm $(patsubst %.c, %, $(wildcard *.c))
