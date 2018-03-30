all: brothers

brothers:
	g++ -Wall -g frati.cpp brothers.cpp -o brothers

clean:
	rm -f brothers bears planning counting