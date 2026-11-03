#!/usr/bin/env bash

curl -s https://raw.githubusercontent.com/LearnWebCode/json-example/master/pets-data.json | \
jq -r '.[] | [.age, .weight] | @tsv'
