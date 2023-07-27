DIR=$1
PROTO_SRC=$2/proto
PROTO_BIN=$3/bin/protoc
PROTO_SOURCE_DIR=$4

echo "The DIR is: " ${DIR}
echo "The PROTO_SRC is: " ${PROTO_SRC}
echo "The PROTO_BIN is: " ${PROTO_BIN}
echo "The proto path is: " ${PROTO_SOURCE_DIR}
echo "The current path is: " ${PWD}

cd ${DIR}
cp -rf ${PROTO_SRC}/ ./ 

OLD_LIB=$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$3/lib:$LD_LIBRARY_PATH
# ${PROTO_BIN} proto/*.proto -I proto --cpp_out  proto
sh ${PROTO_SOURCE_DIR}/generate.sh ${PROTO_SOURCE_DIR}
export LD_LIBRARY_PATH=$OLD_LIB