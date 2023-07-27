# rm -rf *.h *.cc
PROTO_SOURCE_DIR=$1

protoc  ${PROTO_SOURCE_DIR}/sau/*.proto   -I ${PROTO_SOURCE_DIR}/sau  --cpp_out  ${PROTO_SOURCE_DIR}/sau

