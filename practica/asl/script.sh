# escribe el codigo intermedio generado y el codigo original

./asl ../examples/jp_genc_$1.asl > tmp.t
cat -n tmp.t
echo
cat -n ../examples/jp_genc_$1.asl;
echo
rm -f tmp.t
