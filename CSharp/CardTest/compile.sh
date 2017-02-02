#!/bin/bash

error() {
  echo ">>>>>> Failed to compile <<<<<<<<<"
  echo ""

  exit 1
}

trap error ERR

mono tools/nuget/nuget.exe restore -Verbosity detailed
xbuild /p:Configuration=Release

