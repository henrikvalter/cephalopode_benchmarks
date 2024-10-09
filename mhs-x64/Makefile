.PHONY: default dirs fixed compile callgrind clean cleanup

default: clean dirs fixed compile callgrind

dirs:
	mkdir -p src_fixed bin callgrind

fixed:
	python3 script/generate_fixed.py

compile:
	sh script/compile_programs.sh

callgrind:
	sh script/do_callgrind.sh

cleanup:
	-rm src_arb/*.o src_arb/*.hi src_fixed/*
	-rm bin/*

clean: cleanup
	-rm callgrind/*

