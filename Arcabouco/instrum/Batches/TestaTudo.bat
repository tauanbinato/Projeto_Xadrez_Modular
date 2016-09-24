rem testa todos os scripts

cls

if exist ..\scripts\estatisticas.estat  del ..\scripts\estatisticas.estat

..\produto\testearvore        /s..\scripts\testearvore             /l..\produto\testearvore              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testearvoreprod    /s..\scripts\testearvore             /l..\produto\testearvore              /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testearvoredebug   /s..\scripts\testearvore             /l..\produto\testearvoredebug         /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testearvoredebug   /s..\scripts\testecontador           /l..\produto\testecontador            /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testearvoredebug   /s..\scripts\testecontroleespaco     /l..\produto\testecontroleespaco      /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\produto\testearvoredebug   /s..\scripts\testedeturpaarvore      /l..\produto\testedeturpaarvore       /a..\scripts\estatisticas
if errorlevel 4 goto sai

..\..\ferramnt\exbestat /e..\scripts\estatisticas

:sai

