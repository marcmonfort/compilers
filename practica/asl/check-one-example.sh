# escribe el codigo intermedio generado y el codigo original

./asl ../myExamples/jp_genc_$1.asl > tmp.t
cat -n tmp.t
echo
cat -n ../myEexamples/jp_genc_$1.asl;
echo
rm -f tmp.t
