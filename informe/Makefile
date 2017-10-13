TEX_FILES = $(shell find informe -name '*.tex' -or -name '*.sty' -or -name '*.cls')
IMG_FILES = $(shell find informe -path '*.jpg' -or -path '*.png' -or \( \! -path './obj/*.pdf' -path '*.pdf' \) )

all: informe.pdf

informe.pdf: informe.tex $(TEX_FILES) $(IMG_FILES)
	xelatex $<
