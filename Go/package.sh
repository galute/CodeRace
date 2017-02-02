#!/bin/bash

cp ../temp.txt .

docker build -t cardtest_go:1.0 .
