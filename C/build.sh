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
echo building 'C' test App
echo =============================================================================
echo

CURDIR=`pwd`

docker run --rm \
           -v "$CURDIR/:/build" \
           --workdir /build \
           gcc:6 bash ./compile.sh
