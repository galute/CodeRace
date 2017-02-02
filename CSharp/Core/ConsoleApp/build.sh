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

if [ -z "$GO_PIPELINE_COUNTER" ]; then
    export GO_PIPELINE_COUNTER=0
fi

if [ -z "$GO_STAGE_COUNTER" ]; then
    export GO_STAGE_COUNTER=0
fi

CURRENT_DIR=`pwd`

echo
echo =============================================================================
echo building C# dotnet core test App
echo =============================================================================
echo

CURDIR=`pwd`

docker run --rm \
           -v "$CURDIR/:/build" \
           --workdir /build \
           microsoft/dotnet:1.1-sdk-projectjson bash ./compile.sh



