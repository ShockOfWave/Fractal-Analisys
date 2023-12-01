VENV = venv
PYTHON = $(VENV)/bin/python3
PIP = $(VENV)/bin/pip
PYTEST = $(VENV)/bin/pytest
FLAKE8 = $(VENV)/bin/flake8

define find.functions
		@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'
endef

.PHONY: install clean run_example all help tests linter

help:
	@echo 'The following commands can be used.'
	@echo ''
	@echo 'This project calculates TDA for AFM surfaces.'
	@echo 'You can find more calculation by links on our github repository.'
	@echo ''
	@echo ''
	@echo 'All make functions needs Python and virtualenv.'
	@echo ''
	@echo ''
	$(call find.functions)


install: ## cleans venv and build and installs requirements
install:
	rm -rfv build TDA.egg-info venv
	python3 -m venv venv
	$(PIP) install .

clean: ## cleans venv and build
clean:
	rm -rfv build TDA.egg-info venv


run_example: ## runs calculations with example files
run_example:
	$(PYTHON) -m src example_data


all: ## cleans all, rebuild, tests run calculation with example files
all:
	rm -rfv build TDA.egg-info venv
	python3 -m venv venv
	$(PIP) install .
	$(PYTEST) tests
	$(PYTHON) -m src example_data
	$(FLAKE8) src

tests: ## runs tests of lacunarity witn pytest
tests:
	$(PYTEST) tests/test_lacunarity.py

linter: ## runs flake8 linters
linter:
	$(FLAKE8) src