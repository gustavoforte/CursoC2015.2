include cfg.mak

all: $(DIST)/$(EXE)
#	@echo: "Path: $(PATH)"
#	@echo "SRCS=$(wildcard $(SRC)/*.c)"
#	@echo "OBJS=$(wildcard $(OBJ)/*.o)"
	@echo Compilado!
	
$(DIST)/$(EXE): $(OBJS)
	@echo "Compilando $(EXE) ..."
	@gcc $(OBJS) -o $(DIST)/$(EXE)

$(OBJ)/%.o: $(SRC)/%.c
	@echo Compilando $< ...
	@gcc -c $< -I ./$(INC) -o $@

clean:
	@echo Limpando...
	@rm -rf $(OBJ)/*.o
	@rm -rf $(DIST)/$(EXE)
	@echo Limpo!

remake: clean all
	@echo Remake feito!