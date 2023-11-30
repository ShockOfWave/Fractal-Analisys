VENV = venv
PYTHON = $(VENV)/bin/python3
PIP = $(VENV)/bin/pip

define find.functions
		@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'
endef

.PHONY: install clean run_example all help lacunarity_test

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


all: ## cleans all, rebuild and run calculation with example files
all:
	rm -rfv build TDA.egg-info venv
	python3 -m venv venv
	$(PIP) install .
	$(PYTHON) -m src example_data

lacunarity_test: ## runs tests of lacunarity witn pytest
lacunarity_test:
	$(PYTHON) -m pytest tests/test_lacunarity.py