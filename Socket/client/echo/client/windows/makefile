include cfg.mak

all: $(DIST) $(OBJ) $(DIST)/$(EXE)
	@echo Compilado!

$(DIST):
	@echo Criando diretorio $(DIST) ...
	@mkdir $(DIST)

$(OBJ):
	@echo Criando diretorio $(OBJ) ...
	@mkdir $(OBJ)

$(DIST)/$(EXE): $(OBJS)
	@echo Compilando $(EXE)...
	@gcc $(OBJS) $(GCCARGS) -o $(DIST)/$(EXE)

$(OBJ)/%.o: $(SRC)/%.c
	@echo Compilando $< ...
	@gcc -c $< $(GCCARGS) -I ./$(INC) -o $@

clean:
	@echo Limpando...
	@rm -rf $(OBJ)/*.o $(DIST)/$(EXE)

remake: clean all
