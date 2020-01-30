SHELL=/bin/bash

ifndef ELASTIC_VERSION
ELASTIC_VERSION := $(shell awk 'BEGIN { FS = "[= ]" } /^ELASTIC_VERSION=/ { print $$2 }' .env)
endif
export ELASTIC_VERSION

ifndef GIT_BRANCH
GIT_BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
endif

TARGETS := apm-server elasticsearch logstash kibana beats

images: $(TARGETS)
push: $(TARGETS:%=%-push)
clean: $(TARGETS:%=%-clean)

$(TARGETS): $(TARGETS:%=%-checkout)
	(cd stack/$@ && make)

$(TARGETS:%=%-push): $(TARGETS:%=%-checkout)
	(cd stack/$(@:%-push=%) && make push)

$(TARGETS:%=%-checkout):
	test -d stack/$(@:%-checkout=%) || \
          git clone https://github.com/elastic/$(@:%-checkout=%)-docker.git stack/$(@:%-checkout=%)
	(cd stack/$(@:%-checkout=%) && git fetch && git reset --hard && git checkout origin/$(GIT_BRANCH))

$(TARGETS:%=%-clean):
	rm -rf stack/$(@:%-clean=%) && find . -name "*.keystore" -exec rm -f {} \; && \
		docker-compose -f docker-compose.setup.yml -f docker-compose.yml down --remove-orphans && \
		docker-compose -f setup.yml down --remove-orphans && \
		docker volume rm stack-docker_es_data

