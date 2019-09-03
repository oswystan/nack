a.out: nack_test.cc nack.cc nack.h
	g++ -o $@ $^
clean:
	rm -f a.out
