#!/bin/bash

SRC_DIR="./src/"
DST_DIR="data_proto"
test -e $DST_DIR || mkdir $DST_DIR

protoc -I=$SRC_DIR --cpp_out=$DST_DIR ${SRC_DIR}road.prototxt
