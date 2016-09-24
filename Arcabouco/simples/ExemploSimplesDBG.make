##################################################
###
### Diretivas de MAKE para o construto: ExemploSimplesDBG
### Gerado a partir de: ExemploSimplesDbg.comp
###
### ----- Arquivo gerado, N�O EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = ExemploSimplesDBG


### Nomes de paths

Pobj                 = .
Perr                 = .
PDEFAULT             = .
Pespstr              = .
Plista               = .
Pc                   = .

### Nomes de diret�rios para gera��o

Fobj                 = .
Ferr                 = .
FDEFAULT             = .
Fespstr              = .
Flista               = .
Fc                   = .

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de gera��o

all : limpa \
   $(Fobj)\TestArv.obj   $(Fobj)\Arvore.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Depend�ncias de m�dulos objeto a compilar

$(Fobj)\TestArv.obj :  {$(Pc)}\TestArv.c \
    {$(PDEFAULT)}TST_ESPC.H           {$(PDEFAULT)}TST_Espc.h           {$(PDEFAULT)}arvore.h             \
    {$(PDEFAULT)}generico.h           {$(PDEFAULT)}lerparm.h           
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Arvore.obj :  {$(Pc)}\Arvore.c \
    {$(PDEFAULT)}ARVORE.H            
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err


### Termina��o

Construto : \
   $(Fobj)\TestArv.obj   $(Fobj)\Arvore.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: ExemploSimplesDBG
###
##################################################

