lowly_files = LOWLY/buffer_trains/buffer_trains.c LOWLY/tokenizer/tokenizer.c
c = gcc

compile_all:
	@mkdir -p output
	$(c) -g $(lowly_files) tests/buffer_train_test.c -o output/buffer_train_test
	$(c) -g $(lowly_files) tests/tokenizer_test.c -o output/tokenizer_test
	$(c) -S -g0 -fverbose-asm LOWLY/buffer_trains/buffer_trains.c -o output/buffer_trains.s
	$(c) -S -g0 -fverbose-asm LOWLY/tokenizer/tokenizer.c -o output/tokenizer.s
	./output/buffer_train_test
	./output/tokenizer_test
