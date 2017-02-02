#!/bin/bash

error() {
  echo ">>>>>> Failed to compile <<<<<<<<<"
  echo ""

  exit 1
}

trap error ERR

dotnet restore
dotnet build -c Release **/project.json


