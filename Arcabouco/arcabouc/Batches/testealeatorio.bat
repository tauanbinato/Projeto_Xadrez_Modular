REM Teste de gera numeros aleatorios
pushd  .
cd ..\..\ferramnt
gmake  /B..\arcabouc\composicao /CTesteAleatorio

del ..\produto\*.err
del ..\objetos\*.obj

cd ..\arcabouc\batches
nmake /F..\composicao\testealeatorio.make 

popd

..\produto\testealeatorio /s..\scripts\testealeatorio
