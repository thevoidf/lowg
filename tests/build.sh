g++ -I../deps -I/usr/include/freetype2 -L../lib ../objs/*.o $1 -o $2 -lglfw -lrt -lm -ldl -lfreeimage -lfreetype -lfreetype-gl -lz -lpng16 -lm -lz -lm
