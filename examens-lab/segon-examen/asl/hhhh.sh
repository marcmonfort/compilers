# escribe el resultado de mi ejecucion y de la ejecucion correcta

f="../jps/jp_genc_$1.asl";
./asl "$f" > tmp.t
../tvm/tvm tmp.t #  < "${f/asl/in}" > tmp.out
echo _____mine_____:
cat tmp.out
echo _____Good_____:
cat "${f/asl/out}"
rm -f tmp.out