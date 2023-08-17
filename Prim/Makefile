CC = g++
CFLAGS =
COPTFLAGS = -O3 -g
LDFLAGS =

prim: prim.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ prim mst.txt