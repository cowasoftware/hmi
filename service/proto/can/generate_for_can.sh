# rm -rf *.h *.cc
PROTO_SOURCE_DIR=$1

protoc  ${PROTO_SOURCE_DIR}/can/*.proto   -I ${PROTO_SOURCE_DIR}/can  --cpp_out  ${PROTO_SOURCE_DIR}/can

