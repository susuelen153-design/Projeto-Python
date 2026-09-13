# dataset/

```
dataset/
├── data.yaml     modelo de referencia (o valido e o do export do Roboflow)
├── raw/          fotos cruas da ESP32-CAM, separadas por classe
│   ├── garfo/    garfo_001.jpg, garfo_002.jpg, ...
│   └── colher/   colher_001.jpg, colher_002.jpg, ...
└── export/       dataset exportado do Roboflow no formato YOLO
    ├── data.yaml
    ├── train/{images,labels}
    └── valid/{images,labels}
```

As imagens nao sao versionadas no Git (ver `.gitignore`): elas entram no
`CP1_NOME_GRUPO.zip` da entrega. Para o zip, inclua uma **amostra** ou o
dataset exportado completo, conforme o tamanho permitir.
