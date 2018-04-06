build: brothers bears planning counting

brothers:
	g++ -Wall -g frati.cpp brothers.cpp -o brothers

bears:
	# g++ -Wall -g ursi.cpp bears.cpp -o bears

planning:
	g++ -Wall -g planificare.cpp planning.cpp -o planning

counting:
	# g++ -Wall -g numaratoare.cpp counting.cpp -o counting

run-p1:
	./brothers

run-p2:
	# ./bears

run-p3:
	./planning

run-p4:
	# ./counting

clean:
	rm -f brothers bears planning counting