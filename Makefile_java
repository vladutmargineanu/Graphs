PROBLEME := bin/P1.class bin/P2.class bin/P3.class bin/P4.class

build: $(PROBLEME)

bin/%.class: src/%.java
	mkdir -p bin
	javac $^ -d bin

run-p1:      # nume necesar
	java -Xss128M -cp bin P1

run-p2:      # nume necesar
	java -Xss128M -cp bin P2

run-p3:      # nume necesar 
	java -Xss128M -cp bin P3

run-p4:      # nume necesar 
	java -Xss128M -cp bin P4

clean:		 # nume necesar
	rm -rf bin
