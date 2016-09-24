ECHO compila todos os programas exemplo
REM Requer o ambiente (environment) inicializado para compilar com o VisualStudio Microsoft
cls

del ..\produto\*.err
del ..\objetos\*.obj

REM compila para producao sem otimizacoes
pushd .
nmake /F..\composicao\testearvore.make 
popd

REM compila para producao com otimizacoes
del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testearvoreprod.make  "PRD="

REM compila para debug - o arquivo .comp indica quem deve ser compilado com _DEBUG
del ..\objetos\*.obj
pushd .
nmake /F..\composicao\testearvoredebug.make 
del ..\objetos\*.obj

popd

copy ..\produto\*.err ..\produto\tudo.err

notepad ..\produto\tudo.err

