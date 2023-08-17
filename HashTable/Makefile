CC = g++
CFLAGS =
COPTFLAGS = -O3 -g
LDFLAGS =

insert_test: insert_test.o
	$(CC) $(COPTFLAGS) -o $@ $^

search_test: search_test.o
	$(CC) $(COPTFLAGS) -o $@ $^

edit_distance: edit_distance.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ insert_test search_test edit_distance

