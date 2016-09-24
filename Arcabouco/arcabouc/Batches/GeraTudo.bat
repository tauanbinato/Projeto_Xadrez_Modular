@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\..\ferramnt

gmake  /b..\arcabouc\composicao  /cTesteAleatorio
gmake  /b..\arcabouc\composicao  /cTesteFuncoes
gmake  /b..\arcabouc\composicao  /cTesteControleEspaco
gmake  /b..\arcabouc\composicao  /cTesteTabelaSimbolos
gmake  /b..\arcabouc\composicao  /cTesteContadores
gmake  /b..\arcabouc\composicao  /cTesteLerParametros
gmake  /b..\arcabouc\composicao  /cCriaLib

popd
