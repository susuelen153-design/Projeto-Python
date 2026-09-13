#!/usr/bin/env python3
"""Valida o dataset exportado do Roboflow contra os requisitos do CP01.

Confere: estrutura train/valid com images e labels, data.yaml legivel e
coerente, nomes de arquivo sem espacos/acentos, pareamento imagem<->label,
formato das linhas YOLO (classe cx cy w h normalizados) e a contagem de
imagens por classe.

Uso:
    python validar_dataset.py --dataset ../dataset/export
"""

from __future__ import annotations

import argparse
import re
import sys
from collections import Counter
from pathlib import Path

NOME_VALIDO = re.compile(r"^[A-Za-z0-9._-]+$")
EXT_IMG = {".jpg", ".jpeg", ".png"}


def ler_classes(data_yaml: Path) -> list[str]:
    """Le 'names' do data.yaml sem depender do pacote pyyaml."""
    texto = data_yaml.read_text(encoding="utf-8", errors="replace")

    lista = re.search(r"^names:\s*\[(.*?)\]", texto, re.M | re.S)
    if lista:
        return [n.strip().strip("'\"") for n in lista.group(1).split(",") if n.strip()]

    nomes: list[str] = []
    dentro = False
    for linha in texto.splitlines():
        if re.match(r"^names:\s*$", linha):
            dentro = True
            continue
        if dentro:
            item = re.match(r"^\s*-\s*(.+?)\s*$", linha)
            indexado = re.match(r"^\s*\d+\s*:\s*(.+?)\s*$", linha)
            if item:
                nomes.append(item.group(1).strip("'\""))
            elif indexado:
                nomes.append(indexado.group(1).strip("'\""))
            elif linha.strip() and not linha.startswith((" ", "\t")):
                break
    return nomes


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dataset", required=True, help="pasta do dataset exportado")
    ap.add_argument("--min-por-classe", type=int, default=100,
                    help="minimo de imagens por classe (padrao: 100)")
    args = ap.parse_args()

    raiz = Path(args.dataset).resolve()
    erros: list[str] = []
    avisos: list[str] = []
    print(f"validando: {raiz}\n")

    if not raiz.is_dir():
        print(f"ERRO: pasta nao encontrada: {raiz}", file=sys.stderr)
        return 2

    # --- data.yaml ---------------------------------------------------------
    data_yaml = raiz / "data.yaml"
    classes: list[str] = []
    if not data_yaml.is_file():
        erros.append("data.yaml nao encontrado na raiz do dataset")
    else:
        classes = ler_classes(data_yaml)
        texto = data_yaml.read_text(encoding="utf-8", errors="replace")
        nc = re.search(r"^nc:\s*(\d+)", texto, re.M)
        if not classes:
            erros.append("data.yaml: nao foi possivel ler a lista 'names'")
        if nc and classes and int(nc.group(1)) != len(classes):
            erros.append(f"data.yaml: nc={nc.group(1)} difere de len(names)={len(classes)}")
        if classes and len(classes) < 2:
            erros.append(f"data.yaml: o CP1 exige no minimo 2 classes (encontrado {len(classes)})")
        print(f"classes em data.yaml: {classes}")

    # --- estrutura e conteudo ---------------------------------------------
    total_por_classe: Counter[int] = Counter()
    for split in ("train", "valid"):
        img_dir, lbl_dir = raiz / split / "images", raiz / split / "labels"
        if not img_dir.is_dir() or not lbl_dir.is_dir():
            erros.append(f"estrutura ausente: {split}/images e {split}/labels")
            continue

        imagens = [p for p in sorted(img_dir.iterdir()) if p.suffix.lower() in EXT_IMG]
        if not imagens:
            erros.append(f"{split}/images esta vazia")

        sem_objeto = 0
        for img in imagens:
            if not NOME_VALIDO.match(img.name):
                erros.append(f"nome invalido (espaco/acento/caractere especial): {split}/{img.name}")

            label = lbl_dir / (img.stem + ".txt")
            if not label.is_file():
                erros.append(f"imagem sem label: {split}/images/{img.name}")
                continue

            linhas = [l for l in label.read_text(errors="replace").splitlines() if l.strip()]
            if not linhas:
                sem_objeto += 1
                continue

            for n, linha in enumerate(linhas, 1):
                partes = linha.split()
                if len(partes) != 5:
                    erros.append(f"{split}/labels/{label.name}:{n} deveria ter 5 campos")
                    continue
                try:
                    cid = int(partes[0])
                    valores = [float(v) for v in partes[1:]]
                except ValueError:
                    erros.append(f"{split}/labels/{label.name}:{n} contem valor nao numerico")
                    continue
                if classes and not (0 <= cid < len(classes)):
                    erros.append(f"{split}/labels/{label.name}:{n} classe {cid} fora do data.yaml")
                if any(not 0.0 <= v <= 1.0 for v in valores):
                    erros.append(f"{split}/labels/{label.name}:{n} coordenadas fora de 0..1")
                if valores[2] <= 0 or valores[3] <= 0:
                    erros.append(f"{split}/labels/{label.name}:{n} bounding box com largura/altura zero")
                total_por_classe[cid] += 1

        if sem_objeto:
            avisos.append(f"{split}: {sem_objeto} imagem(ns) sem nenhum objeto anotado")
        print(f"{split}: {len(imagens)} imagens")

    # --- contagem por classe ----------------------------------------------
    print("\nanotacoes por classe:")
    for cid in range(len(classes) or (max(total_por_classe) + 1 if total_por_classe else 0)):
        nome = classes[cid] if cid < len(classes) else f"classe_{cid}"
        qtd = total_por_classe.get(cid, 0)
        marca = "ok " if qtd >= args.min_por_classe else "!! "
        print(f"  {marca}{nome}: {qtd} bounding boxes")
        if qtd < args.min_por_classe:
            avisos.append(f"classe '{nome}' com {qtd} anotacoes "
                          f"(minimo recomendado: {args.min_por_classe})")

    # --- resultado ---------------------------------------------------------
    print()
    for a in avisos:
        print(f"AVISO: {a}")
    for e in erros[:40]:
        print(f"ERRO : {e}")
    if len(erros) > 40:
        print(f"... e mais {len(erros) - 40} erro(s)")

    if erros:
        print(f"\nresultado: {len(erros)} erro(s). Corrija antes de entregar.")
        return 1
    print("\nresultado: dataset dentro dos requisitos do CP1.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
