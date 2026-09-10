# Content Schema

JSON input for `scripts/generate.py`.

## Top-Level Fields

| Field | Type | Required | Description |
|-------|------|----------|-------------|
| `title` | string | yes | Main title (uppercase recommended) |
| `subtitle` | string[] | no | Subtitle lines below main title |
| `subtitle_note` | string | no | Italic note below subtitle |
| `meta` | object[] | no | Cover page metadata: `{label, value}` |
| `sections` | object[] | yes | Document sections (see below) |
| `output_dir` | string | no | Output directory (default: user Downloads) |
| `filename` | string | no | Base filename without extension |

## Section Object

| Field | Type | Required | Description |
|-------|------|----------|-------------|
| `title` | string | yes | Section title (e.g. "1. CONTEXTO") |
| `body` | string[] | no | Paragraph text blocks |
| `bullets` | object[] | no | Bullet items: `{text, level}` (level 0 or 1) |
| `tables` | object[] | no | Tables (see below) |
| `subsections` | object[] | no | Nested sections with same structure |
| `bold_body` | bool | no | Make first body paragraph bold |

## Table Object

| Field | Type | Required | Description |
|-------|------|----------|-------------|
| `headers` | string[] | yes | Column headers |
| `rows` | string[][] | yes | Row data (each row is array of strings) |
| `col_widths` | number[] | no | Column widths in mm (default: equal split) |

## Bullet Object

| Field | Type | Required | Description |
|-------|------|----------|-------------|
| `text` | string | yes | Bullet content |
| `level` | number | no | Indent level (0 = primary, 1 = sub-bullet) |

## Meta Object

| Field | Type | Required | Description |
|-------|------|----------|-------------|
| `label` | string | yes | Label (bold) |
| `value` | string | yes | Value (regular) |

## Example

```json
{
  "title": "DESCRICAO DO PROBLEMA",
  "subtitle": ["Sompo Seguros", "Sprint 1: Data Science"],
  "subtitle_note": "Documento Tecnico",
  "meta": [
    {"label": "Elaborado por:", "value": "Israel Toledo"},
    {"label": "Data:", "value": "08 de maio de 2026"}
  ],
  "filename": "Sprint1_Descricao_Problema",
  "output_dir": "C:/Users/israel.toledo/Documents/FIAP/FIAP-SOMPO/SPRINT1-DATA-SCIENCE",
  "sections": [
    {
      "title": "1. O PROBLEMA",
      "body": ["Paragraph one about context."],
      "bullets": [
        {"text": "First point", "level": 0}
      ],
      "subsections": [
        {
          "title": "1.1 Detalhes",
          "tables": [
            {
              "headers": ["Col A", "Col B", "Col C"],
              "rows": [["val1", "val2", "val3"]],
              "col_widths": [35, 55, 100]
            }
          ]
        }
      ]
    }
  ]
}
```
