#!/bin/sh
echo '###################################################'
echo 'Compiling java CardTest...'
echo '###################################################'
CURDIR=`pwd`

docker run --rm \
           -v "${CURDIR}/:/build" \
           --workdir /build \
           openjdk:9-jdk javac ./src/cardtest/CardTest.java
echo '###################################################'
echo "Compile complete, building docker image"
echo '###################################################'
cp ../../temp.txt .

docker build -t cardtest_java:1.0 .

echo '###################################################'
echo "Build Complete"
echo '###################################################'
