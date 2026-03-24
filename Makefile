# taikinys: priklausomybes
#	kodas

CXX = g++
CXXFLAGS = -O3 -std=c++20 # O3 vėliavėlė — optimizuoja programą
OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src

# .o failų sąrašas
OBJS = $(OBJ_DIR)/pagr.o \
       $(OBJ_DIR)/ivestis.o \
       $(OBJ_DIR)/isvestis.o \
       $(OBJ_DIR)/ivesties_pagalb_fjos.o \
       $(OBJ_DIR)/isvesties_pagalb_fjos.o \
       $(OBJ_DIR)/strukturu_metodai.o \
       $(OBJ_DIR)/klaidu_valdymas.o

# Pagrindinis taikinys
$(BIN_DIR)/programa: $(OBJS)
	$(CXX) $(OBJS) -o $(BIN_DIR)/programa $(LDFLAGS)

# taisyklė visiem .o failam
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# $<, $@ — automatiniai kintamieji
# $< — nurodo pirmąją priklausomybę (taikinys: PRIKLAUSOMYBĖ) (xxx.o: XXX.CPP)
# $@ — nurodo taikinį/tikslą (TAIKINYS: priklausomybė) (XXX.O: xxx.cpp)

# nurodom, kad visi .o failai priklauso nuo visų .h failų
$(OBJS): $(SRC_DIR)/*.h

clean:
	del $(OBJ_DIR)\*.o
	del $(BIN_DIR)\programa.exe

run: $(BIN_DIR)/programa
	./$(BIN_DIR)/programa

# bin/programa: obj/pagr.o obj/ivestis.o obj/isvestis.o obj/ivesties_pagalb_fjos.o obj/isvesties_pagalb_fjos.o obj/strukturu_metodai.o obj/klaidu_valdymas.o
# 	g++ obj/pagr.o obj/ivestis.o obj/isvestis.o obj/ivesties_pagalb_fjos.o obj/isvesties_pagalb_fjos.o obj/strukturu_metodai.o obj/klaidu_valdymas.o -o bin/programa

# obj/pagr.o: src/pagr.cpp
# 	g++ -c src/pagr.cpp -o obj/pagr.o

# obj/ivestis.o: src/ivestis.cpp
# 	g++ -c src/ivestis.cpp -o obj/ivestis.o

# obj/isvestis.o: src/isvestis.cpp
# 	g++ -c src/isvestis.cpp -o obj/isvestis.o

# obj/ivesties_pagalb_fjos.o: src/ivesties_pagalb_fjos.cpp
# 	g++ -c src/ivesties_pagalb_fjos.cpp -o obj/ivesties_pagalb_fjos.o

# obj/isvesties_pagalb_fjos.o: src/isvesties_pagalb_fjos.cpp
# 	g++ -c src/isvesties_pagalb_fjos.cpp -o obj/isvesties_pagalb_fjos.o

# obj/strukturu_metodai.o: src/strukturu_metodai.cpp
# 	g++ -c src/strukturu_metodai.cpp -o obj/strukturu_metodai.o

# obj/klaidu_valdymas.o: src/klaidu_valdymas.cpp
# 	g++ -c src/klaidu_valdymas.cpp -o obj/klaidu_valdymas.o


# # istrins visus .o failus ir pagr.exe faila
# clean:
# 	del obj/*.o
# 	del bin/programa

# run: bin/programa
# 	./bin/programa



