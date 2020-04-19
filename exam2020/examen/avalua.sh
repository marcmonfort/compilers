#! /bin/bash

#################################################
#
#  Examens de laboratori de CL 
# 
#  Script de verificacio de jocs de proves 
#
#  Aquest script ha d'estar situat en el directori arrel de 
#  la practica, que ha de contenir els subdirectoris
#  'asl', 'common', i 'jps'
#
#  Us:  ./avalua.sh
#
#  Executa els jocs de proves dels directoris
#  ./jps
#
#  El resultat de l'script es una llista de quins 
#  jocs de proves se superen i quins no
#
#  Els resultats d'aquest script son orientatius, 
#  i no suposen cap compromís respecte a la qualificacio 
#  final de l'examen.
#
#################################################



##--------- funcions auxiliars --------------------
function update_scores {

    echo -e "$f:\t$1"

    if (test $MODE != "examen"); then 
        smax=`grep $f $JPDIR/scores.dat | cut -d' ' -f2`
        s=0
        if [ "$1" = "OK" ]; then
            s=$smax
        fi
        score=`bc <<< "$score+$s"`
        score_max=`bc <<< "$score_max+$smax"`
    fi
}

## ------------ MAIN -----------------
if (test "x$MODE" == "x"); then MODE="examen"; fi

BASEDIR=$(readlink -f `dirname $0`)
JPDIR=$BASEDIR/jps

# build interpreter
pushd $BASEDIR/asl > /dev/null
make pristine
make antlr
make
popd > /dev/null

# inicialitzar comptadors
if (test $MODE != "examen"); then
   score=0
   score_max=0
fi

# executar gramatica sobre els jps
rm -f $JPDIR/*.student.*
if (test `ls -1 $JPDIR/jp*_chkt_*.asl 2>/dev/null | wc -l ` -gt 0); then
    echo "==============================="
    echo ""
    echo "     Exercici ASL. Typecheck"
    echo ""
    for jp in $JPDIR/jp*_chkt_*.asl; do
        f=`basename $jp .asl`

        # execute test suite
        $BASEDIR/asl/asl $jp |& egrep "^L|^l" >& $JPDIR/$f.student.err

        # compare produced errors with expected errors
        if (diff -q -s $JPDIR/$f.err $JPDIR/$f.student.err &>/dev/null ); then err="OK"
        else err="NO"
        fi
        rm -f $JPDIR/$f.student.err    

        update_scores $err
    done
    echo "==============================="
fi

if (test `ls -1 $JPDIR/jp*_genc_*.asl 2>/dev/null | wc -l ` -gt 0); then
    echo "==============================="
    echo ""
    echo "     Exercici ASL. CodeGen"
    echo ""
    for jp in $JPDIR/jp*_genc_*.asl; do
        f=`basename $jp .asl`

        # exectute test suite
        $BASEDIR/asl/asl $jp >& $JPDIR/$f.student.t
        $BASEDIR/tvm/tvm $JPDIR/$f.student.t < $JPDIR/$f.in > $JPDIR/$f.student.out

        # compare produced output with expected output
        if ( ! test -f $JPDIR/$f.out || ! test -s $JPDIR/$f.out); then out="-"
        elif ( diff -q -s $JPDIR/$f.out $JPDIR/$f.student.out &>/dev/null ); then out="OK"
        else out="NO"
        fi
        rm -f $JPDIR/$f.student.t $JPDIR/$f.student.out
    
        update_scores $out
    done
    echo "==============================="
fi

##---- escriure nota total  
if (test $MODE != "examen"); then
    echo ""
    echo -n "     Nota: "
    score10=`bc <<< "scale=2; 10*$score/$score_max"`
    echo "$score $score_max $score10"
fi

