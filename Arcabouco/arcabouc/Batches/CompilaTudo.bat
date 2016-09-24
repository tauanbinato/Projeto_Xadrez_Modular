ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\objetos\*.obj

pushd .
nmake /F..\composicao\testefuncoes.make 
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testeAleatorio.make  
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testeTabelasimbolos.make  
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testeContadores.make  
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testeLerParametros.make  
popd

del ..\objetos\*.obj
pushd .
nmake /F..\composicao\TesteControleEspaco.make  
popd

del ..\objetos\*.obj
del ..\objetos\*.lib
pushd .
nmake /F..\composicao\CriaLib.make  "PRD="
popd

del ..\objetos\*.obj
..\..\ferramnt\compilebanner  /cMensagensCompilacao
copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err
goto sai

:sai
