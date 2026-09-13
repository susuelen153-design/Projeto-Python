#!/usr/bin/env python3
"""Coleta em lote de imagens da ESP32-CAM para o dataset do CP01.

Baixa fotos da rota /capture do firmware e salva ja com o nome padronizado
(classe_001.jpg, classe_002.jpg, ...), sem espacos, acentos ou caracteres
especiais, continuando a numeracao caso a pasta ja tenha imagens.

Exemplos:
    python coletar_imagens.py --ip 192.168.0.42 --classe garfo --qtd 100
    python coletar_imagens.py --ip 192.168.0.42 --classe colher --qtd 50 --intervalo 1.5
"""

from __future__ import annotations

import argparse
import re
import sys
import time
from pathlib import Path
from urllib.error import URLError
from urllib.request import urlopen

PADRAO_NOME = re.compile(r"^[a-z0-9_]+$")
TAMANHO_MINIMO_BYTES = 3 * 1024  # abaixo disso a captura provavelmente falhou


def proximo_indice(pasta: Path, classe: str) -> int:
    """Retorna o proximo numero livre para a classe dentro da pasta."""
    maior = 0
    for arquivo in pasta.glob(f"{classe}_*.jpg"):
        miolo = arquivo.stem.rsplit("_", 1)[-1]
        if miolo.isdigit():
            maior = max(maior, int(miolo))
    return maior + 1


def baixar(url: str, timeout: float) -> bytes:
    with urlopen(url, timeout=timeout) as resposta:
        return resposta.read()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--ip", required=True, help="IP mostrado no Serial Monitor, ex: 192.168.0.42")
    ap.add_argument("--classe", required=True, help="nome da classe (minusculas, sem acento)")
    ap.add_argument("--qtd", type=int, default=100, help="quantas imagens capturar (padrao: 100)")
    ap.add_argument("--intervalo", type=float, default=1.2,
                    help="segundos entre capturas (padrao: 1.2)")
    ap.add_argument("--saida", default="../dataset/raw",
                    help="pasta de destino (padrao: ../dataset/raw)")
    ap.add_argument("--timeout", type=float, default=12.0, help="timeout HTTP em segundos")
    args = ap.parse_args()

    classe = args.classe.strip().lower()
    if not PADRAO_NOME.match(classe):
        print(f"ERRO: classe '{args.classe}' invalida. Use apenas a-z, 0-9 e _", file=sys.stderr)
        return 2

    destino = (Path(__file__).parent / args.saida / classe).resolve()
    destino.mkdir(parents=True, exist_ok=True)

    url = f"http://{args.ip}/capture"
    indice = proximo_indice(destino, classe)

    print(f"origem : {url}")
    print(f"destino: {destino}")
    print(f"classe : {classe}  |  iniciando em {classe}_{indice:03d}.jpg")
    print("Varie angulo, distancia, iluminacao, posicao e fundo durante a coleta.\n")

    salvas = falhas = 0
    try:
        for _ in range(args.qtd):
            nome = f"{classe}_{indice:03d}.jpg"
            try:
                dados = baixar(f"{url}?t={time.time()}", args.timeout)
            except (URLError, OSError) as erro:
                falhas += 1
                print(f"  falha  {nome}: {erro}")
                if falhas >= 5 and salvas == 0:
                    print("\nVerifique o IP e se o notebook esta na MESMA rede 2.4 GHz.",
                          file=sys.stderr)
                    return 1
                time.sleep(args.intervalo)
                continue

            if len(dados) < TAMANHO_MINIMO_BYTES or not dados.startswith(b"\xff\xd8"):
                falhas += 1
                print(f"  descartada {nome}: resposta nao e um JPEG valido ({len(dados)} bytes)")
                time.sleep(args.intervalo)
                continue

            (destino / nome).write_bytes(dados)
            salvas += 1
            indice += 1
            print(f"  ok     {nome}  ({len(dados)/1024:.0f} kB)")
            time.sleep(args.intervalo)
    except KeyboardInterrupt:
        print("\ninterrompido pelo usuario")

    total_classe = len(list(destino.glob(f"{classe}_*.jpg")))
    print(f"\nsalvas agora: {salvas} | falhas: {falhas}")
    print(f"total da classe '{classe}': {total_classe} imagens")
    if total_classe < 100:
        print(f"ATENCAO: faltam {100 - total_classe} imagens para o minimo exigido (100).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
