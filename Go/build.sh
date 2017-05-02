#!/bin/bash

error() {

  echo ">>>>>> Failed to build <<<<<<<<<"
  echo ""

  exit 1
}

cleanup() {
  cd $CURRENT_DIR

  docker run -v /var/run/docker.sock:/var/run/docker.sock -v /var/lib/docker:/var/lib/docker --rm martin/docker-cleanup-volumes
}

trap error ERR
trap cleanup EXIT

CURRENT_DIR=`pwd`

echo
echo =============================================================================
echo building GoLang test App
echo =============================================================================
echo

CURDIR=`pwd`

docker run --rm \
           -v "$CURDIR/:/go" \
           --workdir /go \
           golang:1.8 bash ./compile.sh
