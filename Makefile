# taikinys: priklausomybes
#	kodas

programa: pagr.o ivestis.o isvestis.o ivesties_pagalb_fjos.o isvesties_pagalb_fjos.o strukturu_metodai.o
	g++ pagr.o ivestis.o isvestis.o ivesties_pagalb_fjos.o isvesties_pagalb_fjos.o strukturu_metodai.o -o programa

pagr.o: pagr.cpp
	g++ -c pagr.cpp

ivestis.o: ivestis.cpp
	g++ -c ivestis.cpp

isvestis.o: isvestis.cpp
	g++ -c isvestis.cpp

ivesties_pagalb_fjos.o: ivesties_pagalb_fjos.cpp
	g++ -c ivesties_pagalb_fjos.cpp

isvesties_pagalb_fjos.o: isvesties_pagalb_fjos.cpp
	g++ -c isvesties_pagalb_fjos.cpp

strukturu_metodai.o: strukturu_metodai.cpp
	g++ -c strukturu_metodai.cpp

# istrins visus .o failus ir pagr.exe faila
clean:
	rm *.o pagr



