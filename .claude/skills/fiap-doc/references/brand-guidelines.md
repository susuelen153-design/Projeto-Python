# FIAP Brand Guidelines | Document Template

## Colors

| Name | Hex | RGB | Usage |
|------|-----|-----|-------|
| FIAP Magenta | `#ED1165` | (237, 17, 101) | Section titles, table headers, accents |
| Black | `#000000` | (0, 0, 0) | Subsection titles, primary text |
| Dark Gray | `#333333` | (51, 51, 51) | Body text |
| Mid Gray | `#B4B4B4` | (180, 180, 180) | Page counter, subtle text |
| Light Gray | `#F5F5F5` | (245, 245, 245) | Alternating table row background |
| White | `#FFFFFF` | (255, 255, 255) | Table header text, primary background |

## Typography

- **Font family:** Montserrat (Google Fonts, SIL Open Font License)
- **Variants used:** Regular (400), Bold (700), Italic, Bold Italic
- **Body text:** 9pt Regular, Dark Gray
- **Section titles:** 13pt Bold, FIAP Magenta, with 0.8mm underline
- **Subsection titles:** 10pt Bold, Black
- **Table headers:** 8pt Bold, White on Magenta background
- **Table cells:** 8pt Regular, Dark Gray
- **Page counter:** 7pt Italic, Mid Gray, right-aligned, number only
- **Cover title:** 28pt Bold, Magenta (wraps within margins via multi_cell)
- **Cover subtitle:** 22pt Bold, Black
- **Cover note:** 12pt Italic, Dark Gray
- **Cover meta:** 9pt, label Bold (45mm width) + value Regular (wraps with multi_cell)

## Page Layout

- **Format:** A4 (210 x 297mm)
- **Margins:** 10mm left/right
- **Header logo:** top-left, auto-sized by image aspect ratio (max height 14mm). Logo width adapts to actual image proportions, no stretching.
- **Content start:** below header logo + 6mm gap
- **Footer logo:** none (removed per design)
- **Page counter:** bottom-right, y=-10mm
- **Auto page break:** at 25mm margin

## Cover Page

- Title: centered, uppercase, magenta. Wraps automatically within margins.
- Subtitle lines: centered, black.
- Note: centered, italic, dark gray.
- Metadata fields (in order):
  1. **Sala:** código da sala (ex.: 1TIAPZ1)
  2. **Matéria:** nome da disciplina
  3. **Grupo:** nome da equipe
  4. **Integrantes:** um nome por linha, com RM. Value usa `\n` para quebra.

**DO NOT include** Versão or Classificação.

## Writing Style (pt-BR)

Obrigatório em todo conteúdo. O tom é natural, como um colega explicando algo com clareza.

### Tom

- **Natural e direto.** Norma culta do pt-BR na prática. Sem corporatese.
- **Criativo sem ser formal.** Respeitar termos técnicos (telemetria, geofencing, DTC, OEM) mas sem pedantismo.
- **Dinâmico e didático.** O leitor precisa entender de primeira. Escopos definidos que se conectam.

### Formatação

1. **Sem travessões (`—`).** Use `:` para definições e `,` para pausas.
2. **Números em evidência.** O dado fala mais alto que a moldura.
3. **Tabelas podem virar listas** com negrito no nome do item quando a leitura fica mais fluida.
4. **Sem jargões desnecessários**, sem comprometer entendimento técnico de ponta.
5. **Concisão acima de tudo.** Se dá pra dizer em 5 palavras, não use 15.

### Acentuação

- ç, ã, õ, é, ê, á, ó, ú, í, â, ô, à sempre presentes. Nunca strip accents.

## Tables

- Header row: magenta background (#ED1165), white bold text, centered
- Data rows: alternating white / light gray (#F5F5F5)
- Cell borders: light gray (#DCDCDC), 0.2mm
- Bottom border: magenta, 0.5mm
- Page break: repeat header row if table splits across pages

## Naming

"FIAP" sempre em maiúsculas.
