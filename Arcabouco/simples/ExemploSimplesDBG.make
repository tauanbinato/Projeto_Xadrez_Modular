##################################################
###
### Diretivas de MAKE para o construto: ExemploSimplesDBG
### Gerado a partir de: ExemploSimplesDbg.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
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

### Nomes de diretórios para geração

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


### Regras de geração

all : limpa \
   $(Fobj)\TestArv.obj   $(Fobj)\Arvore.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\TestArv.obj :  {$(Pc)}\TestArv.c \
    {$(PDEFAULT)}TST_ESPC.H           {$(PDEFAULT)}TST_Espc.h           {$(PDEFAULT)}arvore.h             \
    {$(PDEFAULT)}generico.h           {$(PDEFAULT)}lerparm.h           
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err

$(Fobj)\Arvore.obj :  {$(Pc)}\Arvore.c \
    {$(PDEFAULT)}ARVORE.H            
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c               >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\TestArv.obj   $(Fobj)\Arvore.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: ExemploSimplesDBG
###
##################################################

