lowly_files = LOWLY/buffer_trains/buffer_trains.c LOWLY/tokenizer/tokenizer.c
c = gcc

compile_all:
	@mkdir -p output
	$(c) -g $(lowly_files) tests/buffer_train_test.c -o output/buffer_train_test
	$(c) -g $(lowly_files) tests/tokenizer_test.c -o output/tokenizer_test
	./output/buffer_train_test
	./output/tokenizer_test
