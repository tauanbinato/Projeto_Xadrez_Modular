@ECHO  OFF
REM  Gera todos os scripts de make

cls

pushd  .

cd ..\..\ferramnt

gmake  /b..\instrum\composicao  /cTesteArvore
gmake  /b..\instrum\composicao  /cTesteArvoreProd
gmake  /b..\instrum\composicao  /cTesteArvoreDebug

popd
