CC = gcc
CFLAGS = -Wall -Wextra -O2
BIN = bin

INCLUDE = -Iimplementation
VERIFY = verification.c
BENCHMARK = benchmark.c

IMPL_SRCS := $(wildcard implementation/*.c)
IMPLS := $(notdir $(IMPL_SRCS:.c=))

$(BIN):
	@mkdir -p $(BIN)

# build verify-<impl>
verify-%: $(VERIFY) implementation/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o bin/$@
	./bin/$@ 

# build profile-<impl> (timing + perf compatible)
profile-%: $(BENCHMARK) implementation/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o bin/$@ -lm
	mkfifo perf_ctl.fifo
	mkfifo perf_ack.fifo
	taskset -c 1 perf stat \
	-e cycles,instructions,branches,branch-misses,cache-misses \
	--control=fifo:perf_ctl.fifo,perf_ack.fifo \
	./bin/$@
	rm -rf perf_ctl.fifo perf_ack.fifo
	

# verify all implementations
verify: $(addprefix verify-,$(IMPLS))
	@echo ""
	@echo "=== Running Verification ==="
	@for exe in $(addprefix bin/verify-,$(IMPLS)); do \
		echo $$exe ; \
		$$exe 256 ; \
		echo ""; \
	done

# profile all implementations
profile: $(addprefix profile-,$(IMPLS))
	@echo ""
	@echo "=== Running Benchmark/Profiling ==="
	@for exe in $(addprefix bin/profile-,$(IMPLS)); do \
		echo $$exe ; \
		taskset -c 2 $$exe 1024 ; \
		echo ""; \
	done

clean:
	rm -f bin/*

# .PHONY: all clean
.PHONY: clean verify benchmark