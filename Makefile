.PHONY: all
all: syntax runtime valid

.PHONY: syntax
syntax:
	! ./unittest tests/syntax/args-unterminated.c
	! ./unittest tests/syntax/missing-unittest.c

.PHONY: runtime
runtime:
	! ./unittest tests/runtime/missing-expected.c

.PHONY: valid
valid:
	./unittest tests/valid/args0.c
	./unittest tests/valid/args1.c
	./unittest tests/valid/argsN.c
	./unittest tests/valid/args-duplicate.c
	./unittest tests/valid/expected-file.c
	rm -f exotic
	./unittest tests/valid/expected-inline.c
	test -f exotic
	./unittest tests/valid/file\ name.c
	./unittest tests/valid/teardown.c
	! ./unittest tests/valid/teardown-failure.c
	! ./unittest tests/valid/teardown-after-failure.c
	test -f teardown-after-failure.flag
	rm -f teardown-after-failure.flag
	./unittest tests/valid/xfail.c
	./unittest tests/valid/xfail-inline.c
	./unittest tests/valid/xfail-file-status.c
	! ./unittest tests/valid/xpass.c

.PHONY: distclean
distclean:
	rm -f args-unterminated
	rm -f args0
	rm -f args1
	rm -f argsN
	rm -f args-duplicate
	rm -f exotic
	rm -f expected-file
	rm -f file\ name
	rm -f missing-expected
	rm -f teardown
	rm -f teardown-after-failure
	rm -f teardown-fail
	rm -f teardown-failure
	rm -f xfail
	rm -f xfail-file-status
	rm -f xfail-inline
	rm -f xpass
