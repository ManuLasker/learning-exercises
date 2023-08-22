.DEFAULT_GOAL := help
environment = "inlined"

help:
		@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

main_b: ## build part1
		@cc main.c -o code.out -lm

main_r: ## run part1
		./code.out

main_a: ## run part1
		make main_b && make main_r

main_d: ## run part1
		@cc -g main.c -o code.out -lm
