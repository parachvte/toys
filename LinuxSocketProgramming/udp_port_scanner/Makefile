SCANNER='udp_port_scanner'

all:
	gcc udp_port_scanner.c -o $(SCANNER)

test22:
	sudo ./$(SCANNER) 192.168.0.241 22

test5353:
	sudo ./$(SCANNER) 192.168.0.241 5353

clean:
	rm $(SCANNER)
