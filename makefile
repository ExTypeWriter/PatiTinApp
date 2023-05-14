# PROG = TestTable
# CC = gcc
# CFLAGS = 'pkg-config --cflags gtk+-3.0'
# LIBS = 'pkg-config --libs gtk+-3.0'

# ${PROG} : ${PROG}.c
# 		 ${CC} ${CFLAGS} -o ${PROG} ${PROG}.c ${LIBS}
# clean : 
# 		rm ${PROG}

MyGtkApp : TestTable.c
		gcc -o Test TestTable.c `pkg-config --cflags --libs gtk+-3.0`

