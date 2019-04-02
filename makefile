all: main sdl

main:
	read -p "Argument: " argument
	make -f makeMain $(argument)

sdl:
	read -p "Argument: " argument
	make -f makeSDL $(argument)
