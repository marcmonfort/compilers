#! /bin/bash

# Aquest script crea el fitxer examen-nom.cognom.tgz que cal pujar al raco

# us:  ./empaqueta.sh

#  Aquest script ha d'estar situat en el directori arrel de 
#  la practica, que ha de contenir els subdirectoris
#  'asl', 'common', i 'jps'
#

BASEDIR=$(dirname $0)

cd $BASEDIR

echo "Nom i cognoms: "
read NAME
echo "Nom: $NAME" > noms.txt
NAME=`echo $NAME | sed 's/ /./g' `

echo "Si has fet la practica en parella, indica el nom del teu company.  Si l'has feta sol, simplement prem <enter>."
read PARTNER
if (test "x$PARTNER" != "x"); then echo "Parella: $PARTNER" >> noms.txt; fi


tar -czvf examen-$NAME.tgz asl/Asl.g4 asl/SymbolsVisitor.* asl/TypeCheckVisitor.* asl/CodeGenVisitor.* noms.txt
