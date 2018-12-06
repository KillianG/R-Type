##
## EPITECH PROJECT, 2018
## Cmakefile
## File description:
## Makefile
##

LIGHT_GREEN = "\033[1;32m"
RESET = "\033[0m"

all: build
	@$(MAKE) -j2 -s -C build
	@cd build && ctest
	@rm -rf Testing

build:
	@cmake -E make_directory build
	@cd build && cmake ..
#	@cmake -E make_directory build
#	@cd build \
#	&& conan install .. --build missing \
#	&& cmake .. -G "Unix Makefiles"

clean:
	@if [ -d build ]; then $(MAKE) -s -C build/ clean; fi

fclean: clean
	@rm -rf build
	@echo -e $(LIGHT_GREEN) \
		 "Removed build directory" \
		 $(RESET)

re: fclean all

test:
	@cd build && ctest

.PHONY: all clean fclean re build
