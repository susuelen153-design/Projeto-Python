# fiap-doc

> Claude Code skill for generating branded FIAP documents (DOCX + PDF)

## What it does

Generates professionally formatted FIAP documents from structured JSON content. Produces both DOCX (editable) and PDF (print-ready) with full brand compliance:

- FIAP Magenta (#ED1165) accents and section titles
- Montserrat font family with full Unicode support (including Portuguese diacritics)
- FIAP header logo (top-left), no footer logo
- Branded tables with alternating row colors
- Smart page breaking
- Cover page with Sala, Matéria, Grupo, Integrantes (one per line)

## Install

```bash
npx skills add iskisraell/fiap-doc -g
```

Or via symlink:

```bash
ln -s ~/.agents/skills/fiap-doc ~/.claude/skills/fiap-doc
```

## Use in Claude Code

> "Generate a new FIAP document with what we've talked here"

Claude will extract content from the conversation, build the JSON, and run the generator.

## Manual use

```bash
pip install -r scripts/requirements.txt
python scripts/generate.py content.json
python scripts/generate.py content.json --pdf-only
python scripts/generate.py content.json --docx-only
```

## Content format

See `references/content-schema.md` for the full JSON schema.

## Brand specs

See `references/brand-guidelines.md` for colors, typography, and layout rules.

## License

MIT
