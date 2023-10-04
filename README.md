# How to use

Para usar o script _run.sh_ execute a seguinte linha de código:

	chmod +x run.sh
	./run.sh [arquivo.c]

Sempre mude o nome do arquivo mips para:

	algoritmo_mips.asm

Faça isso, pois o script apaga qualquer `.asm` que tenha o mesmo nome do `arquivo.c`.

Por exemplo, se você chamasse:

	./run.sh bubble/bubble.c
 O script apagaria o arquivo `bubble.asm`, mas não o `bubble_mips.asm`.
