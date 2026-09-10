---
name: fiap-doc
description: >
  Generate branded FIAP documents (DOCX + PDF) from conversation context.
  Use this skill when the user asks to "generate a FIAP document", "create a branded doc",
  "write a formal document for FIAP", or references the FIAP document template.
  Produces properly formatted documents with FIAP branding (magenta #ED1165, Montserrat font,
  header logo top-left, professional tables). Full Portuguese (pt-BR) diacritics support.
  Applies FIAP writing style: concise, dynamic, didactic, no em-dashes, technical but accessible.
---

Generate branded FIAP documents in both DOCX and PDF formats from conversation context.

## When to Use

- User asks to generate a FIAP document, report, plan, or proposal
- User references "FIAP document", "FIAP template", "branded doc", "documento FIAP"
- User says "generate a new FIAP document with what we've talked here"

## Writing and Copy Rules (pt-BR)

These rules apply to ALL text in the document, including titles, body, bullets, tables and meta. The tone should feel natural, like a colleague explaining something clearly, not a corporate manual.

### Tone

- **Natural e direto.** Escreva como fala, sem官僚ismo. Norma culta do pt-BR na prática.
- **Criativo sem ser formal.** Sem linguagem de "pelo presente instrumento". Respeitar termos técnicos (telemetria, geofencing, DTC, OEM) mas sem pedantismo.
- **Dinâmico e didático.** O leitor precisa entender de primeira. Escopos definidos que se conectam e se relacionam entre si.

### Formatting

- **Sem travessões (`—`).** Use `:` para definições e `,` para pausas. Nunca `—`.
- **Números em evidência.** Deixe o dado falar mais alto que a moldura. `R$1,6 bi` antes do contexto.
- **Tabelas podem virar listas** com negrito no nome do item quando tornam a leitura mais fluida.
- **Sem jargões desnecessários**, mas sem comprometer entendimento técnico de ponta.
- **Concisão acima de tudo.** Se dá pra dizer em 5 palavras, não use 15.

### Acentuação (obrigatório)

- **Nunca strip accents.** ç, ã, õ, é, ê, á, ó, ú, í, â, ô, à sempre presentes.
- JSON salvo em UTF-8.
- Montserrat TTF cobre todos os glifos Latin Extended.

### Cover Page Meta

- **Sem versão e sem classificação.** Apenas: Sala, Matéria, Grupo, Integrantes.
- **Integrantes:** um nome por linha com RM. Usar `\n` para quebra no JSON.

## Cover Page Formatting

```json
{
  "meta": [
    {"label": "Sala:", "value": "1TIAPZ1"},
    {"label": "Matéria:", "value": "Cognitive Data Science"},
    {"label": "Grupo:", "value": "Perceptron"},
    {"label": "Integrantes:", "value": "Nome Sobrenome (RM 000000)\nNome Sobrenome (RM 000001)"}
  ]
}
```

## Process

1. Extract content from conversation context: titles, sections, subsections, bullet points, tables
2. Apply writing rules to all text: remove em-dashes, add accents, make concise, numbers first
3. Determine document metadata from context (sala, matéria, grupo, integrantes)
4. Build a JSON content file following the schema in `references/content-schema.md`
5. Run `python scripts/generate.py <content.json>` to produce DOCX and PDF
6. Report output file paths to user

## Content Schema

Structure the content as JSON. See `references/content-schema.md` for the full schema.

Key fields:
- `title`: main title (uppercase, bold)
- `subtitle`: array of subtitle lines
- `meta`: array of `{label, value}` pairs for the cover page (Sala, Matéria, Grupo, Integrantes)
- `sections`: array of section objects with `title`, optional `body`, `bullets`, `tables`, `subsections`

## Page Layout Behavior

- **Cover page** always gets its own page (page break after cover)
- **Title wraps automatically** within margins (uses multi_cell)
- **Logo auto-sizes** to match actual image aspect ratio (no stretching)
- **Sections flow continuously**, no forced page break between sections
- Smart page break: a new page is added only when <45mm of space remains before a section title

## Brand Guidelines

See `references/brand-guidelines.md` for colors, fonts, and layout rules.

Quick reference:
- Primary magenta: `#ED1165`
- Font: Montserrat (Regular, Bold, Italic, BoldItalic)
- Header logo: top-left, auto-sized by aspect ratio (FIAP logo)
- Footer logo: none (removed per design)
- Page counter: bottom-right, number only

## Output

- DOCX: Microsoft Word compatible, editable
- PDF: Print-ready, with Montserrat fonts embedded
- Both saved to the output_dir specified in JSON (or user's Downloads folder)

## Dependencies

- Python 3.8+ with `fpdf2` and `python-docx` packages
- Fonts bundled in `assets/`
- No external network required (fully offline)

## References

- `references/content-schema.md` — JSON input schema
- `references/brand-guidelines.md` — FIAP brand specs
- `scripts/generate.py` — Document generator script
- `scripts/requirements.txt` — Python dependencies
