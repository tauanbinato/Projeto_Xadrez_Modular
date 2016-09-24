@ECHO  OFF
REM  Gera script de make de todos os exemplos simples

pushd  .

gmake /cExemploSimples       /pgmake
gmake /cExemploSimplesDbg    /pgmake

popd
