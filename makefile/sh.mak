
# If HOME is not defined in makefile, make will regard it as a shell variable
# $$HOME is a shell variable
all:
	@echo ${HOME}
	@echo ${MAKE}
	@echo $$HOME
	x=1;\
	while [ $$x -le 5 ] ;\
    do \
	x = $(($$x + 1));\
	echo $$x;\
	done
