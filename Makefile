# taikinys: priklausomybes
#	kodas

bin/programa: obj/pagr.o obj/ivestis.o obj/isvestis.o obj/ivesties_pagalb_fjos.o obj/isvesties_pagalb_fjos.o obj/strukturu_metodai.o
	g++ obj/pagr.o obj/ivestis.o obj/isvestis.o obj/ivesties_pagalb_fjos.o obj/isvesties_pagalb_fjos.o obj/strukturu_metodai.o -o bin/programa

obj/pagr.o: src/pagr.cpp
	g++ -c src/pagr.cpp -o obj/pagr.o

obj/ivestis.o: src/ivestis.cpp
	g++ -c src/ivestis.cpp -o obj/ivestis.o

obj/isvestis.o: src/isvestis.cpp
	g++ -c src/isvestis.cpp -o obj/isvestis.o

obj/ivesties_pagalb_fjos.o: src/ivesties_pagalb_fjos.cpp
	g++ -c src/ivesties_pagalb_fjos.cpp -o obj/ivesties_pagalb_fjos.o

obj/isvesties_pagalb_fjos.o: src/isvesties_pagalb_fjos.cpp
	g++ -c src/isvesties_pagalb_fjos.cpp -o obj/isvesties_pagalb_fjos.o

obj/strukturu_metodai.o: src/strukturu_metodai.cpp
	g++ -c src/strukturu_metodai.cpp -o obj/strukturu_metodai.o


# istrins visus .o failus ir pagr.exe faila
clean:
	del obj/*.o
	del bin/programa

run: bin/programa
	./bin/programa



