#!/bin/bash

error() {
  echo ">>>>>> Failed to compile <<<<<<<<<"
  echo ""

  exit 1
}

trap error ERR


node install

