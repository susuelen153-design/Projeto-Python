#!/usr/bin/env python3
"""Padroniza os nomes das imagens do dataset do CP01.

Renomeia qualquer arquivo de imagem para o padrao classe_NNN.jpg, removendo
espacos, acentos e caracteres especiais. Use depois de baixar fotos pelo
navegador ou de misturar capturas de sessoes diferentes.

Exemplos:
    python organizar_dataset.py --pasta ../dataset/raw/garfo --classe garfo
    python organizar_dataset.py --pasta ../dataset/raw/garfo --classe garfo --aplicar
"""

from __future__ import annotations

import argparse
import re
import unicodedata
from pathlib import Path

EXTENSOES = {".jpg", ".jpeg", ".png", ".bmp"}


def normalizar(texto: str) -> str:
    sem_acento = unicodedata.normalize("NFKD", texto).encode("ascii", "ignore").decode()
    return re.sub(r"[^a-z0-9_]+", "_", sem_acento.lower()).strip("_")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--pasta", required=True, help="pasta com as imagens da classe")
    ap.add_argument("--classe", required=True, help="nome oficial da classe")
    ap.add_argument("--inicio", type=int, default=1, help="numero inicial (padrao: 1)")
    ap.add_argument("--aplicar", action="store_true",
                    help="efetiva as renomeacoes (sem esta flag, apenas simula)")
    args = ap.parse_args()

    pasta = Path(args.pasta).resolve()
    if not pasta.is_dir():
        print(f"ERRO: pasta nao encontrada: {pasta}")
        return 2

    classe = normalizar(args.classe)
    arquivos = sorted(p for p in pasta.iterdir()
                      if p.is_file() and p.suffix.lower() in EXTENSOES)
    if not arquivos:
        print(f"nenhuma imagem encontrada em {pasta}")
        return 0

    # Duas fases evitam colisao quando o nome final ja existe em outro arquivo.
    temporarios: list[tuple[Path, str]] = []
    indice = args.inicio
    for origem in arquivos:
        final = f"{classe}_{indice:03d}.jpg"
        indice += 1
        if origem.name == final:
            print(f"  ja ok   {origem.name}")
            continue
        print(f"  renomear {origem.name}  ->  {final}")
        temporarios.append((origem, final))

    if not args.aplicar:
        print(f"\nsimulacao: {len(temporarios)} arquivo(s) seriam renomeados."
              "\nRode de novo com --aplicar para efetivar.")
        return 0

    for i, (origem, _) in enumerate(temporarios):
        origem.rename(pasta / f".tmp_cp01_{i}")
    for i, (_, final) in enumerate(temporarios):
        (pasta / f".tmp_cp01_{i}").rename(pasta / final)

    print(f"\n{len(temporarios)} arquivo(s) renomeados. "
          f"Total na pasta: {len(list(pasta.glob(f'{classe}_*.jpg')))}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
