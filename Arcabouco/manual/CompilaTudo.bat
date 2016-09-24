@ECHO  OFF
REM  Compila todos os exemplos simples 

pushd  .

del *.err
del ExemploManual.exe

del *.obj
nmake /Fexemplomanual.make "PRD="

copy  *.err  tudo.err

notepad tudo.err

popd
