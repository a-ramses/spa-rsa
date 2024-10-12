all: run

bigint: bigint.c
	gcc -o bigint bigint.c

run: bigint input.py check.py
	python3 input.py | ./bigint | python3 check.py

clean:
	rm -f bigint

